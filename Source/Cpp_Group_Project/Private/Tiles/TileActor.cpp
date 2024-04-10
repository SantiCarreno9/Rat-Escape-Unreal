// Fill out your copyright notice in the Description page of Project Settings.

#include "Tiles/TileActor.h"
#include "Engine/Engine.h"
//Debug helpers
#include "DrawDebugHelpers.h"

// Sets default values
// called when the GameObject is initialized kinda like the Awake() function in unity
ATileActor::ATileActor()
{
    
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
    

    // calling the mesh for the actor
	TileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("TileMesh"));
	RootComponent = TileMeshComponent;

    invisibleTileMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("invisibleTileMesh"));
    invisibleTileMeshComponent->SetupAttachment(RootComponent);

}

void ATileActor::FindNeighbors()
{
    FVector RayOffsets[] = { FVector(51, 0, 0), FVector(-51, 0, 0), FVector(0, 51, 0), FVector(0, -51, 0) };
    FVector RayDirections[] = { FVector(61, 0, 0), FVector(-61, 0, 0), FVector(0, 61, 0), FVector(0, -61, 0) };

    for (int i = 0; i < 4; ++i)
    {
        FVector Start = GetActorLocation() + RayOffsets[i];
        FVector End = Start + RayDirections[i];

        FHitResult Hit;
        FCollisionQueryParams Params;
        Params.AddIgnoredActor(this);

        if (GetWorld()->LineTraceSingleByChannel(Hit, Start, End, ECC_GameTraceChannel1, Params))
        {
            if (Hit.bBlockingHit && Hit.GetActor()->IsA(ATileActor::StaticClass()))
            {
                Neighbors.Add(Cast<ATileActor>(Hit.GetActor()));
                // Debug message
                //FString DebugMessage = FString::Printf(TEXT("Actor %s found"), *GetName());
                //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
            }
        }

        // Debug Lines
        //DrawDebugLine(GetWorld(), Start, End, (i < 2) ? FColor::Green : FColor::Blue, true, -1, 1, (i < 2) ? 2 : 1);
    }
}

void ATileActor::OnTileOverlap(
    UPrimitiveComponent* OverlappedComponent,
    AActor* OtherActor,
    UPrimitiveComponent* OtherComp,
    int32 OtherBodyIndex,
    bool bFromSweep,
    const FHitResult& SweepResult)
{
    // Debug message
    //FString DebugMessage = FString::Printf(TEXT("Character %s overlapped"), "DebugAlert");
    //GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
    if (OtherActor && OtherActor->IsA<ACustomCharacter>() && TileState != ETileState::Disabled)
    {
        SteppedOn();
    }
}


TArray<ATileActor*> ATileActor::GetNeighbors() const
{
    return Neighbors;
}

void ATileActor::SetEnabled()
{
    if (TileState != ETileState::Disabled)
    {
        TileState = ETileState::Enabled;
        TileMeshComponent->SetMaterial(0, TileMaterials[0]);
    }
    else { SetDisabled(); }
}

void ATileActor::SetDisabled()
{
    TileState = ETileState::Disabled;
    TileMeshComponent->SetMaterial(0, TileMaterials[2]);
}

void ATileActor::SteppedOn()
{
    if (TileState == ETileState::Enabled)
    {
        TileState = ETileState::SteppedOn;
        TileMeshComponent->SetMaterial(0, TileMaterials[1]);

        // Invoke the event to notify state change
        OnStateChanged.Broadcast(this);
    }
}

// Called when the game starts or when spawned
void ATileActor::BeginPlay()
{
	Super::BeginPlay();

    
    

    // find my neighbors
    FindNeighbors();

    // wait for being touched
    invisibleTileMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ATileActor::OnTileOverlap);

    // Call the initialState, in case the state is disabled
    SetEnabled();
    
}

// Called every frame
//void ATileActor::Tick(float DeltaTime)
//{
//	Super::Tick(DeltaTime);
//
//}

