// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMeshComponent;

}

// Called when the game starts or when spawned
void ADoorActor::BeginPlay()
{
	Super::BeginPlay();

    TArray<AActor*> FoundActors;
    UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Tiles", FoundActors);

    for (AActor* FoundActor : FoundActors)
    {
        ATileActor* Tile = Cast<ATileActor>(FoundActor);
        if (Tile)
        {
            Tile->OnStateChanged.AddDynamic(this, &ADoorActor::HandleTileStateChanged);
            Tiles.Add(Tile);
            if (Tile->GetState() == ETileState::Enabled)
            {
                EnabledTiles.Add(Tile);
            }
        }
    }
	
}

void ADoorActor::HandleTileStateChanged(ATileActor* Tile)
{
    if (Tile->GetState() == ETileState::SteppedOn && EnabledTiles.Contains(Tile))
    {
        EnabledTiles.Empty();
        UpdateEnabledTiles(Tile);
    }
    else if (!EnabledTiles.Contains(Tile))
    {
        EnableAllTiles();
    }
}

void ADoorActor::UpdateEnabledTiles(ATileActor* ChangedTile)
{
    TArray<ATileActor*> Neighbors = ChangedTile->GetNeighbors();

    for (ATileActor* Neighbor : Neighbors)
    {
        if (Neighbor && Neighbor->GetState() == ETileState::Enabled)
        {
            EnabledTiles.Add(Neighbor);
        }
    }

    if (!CheckEnabled())
    {
        FString DebugMessage = FString::Printf(TEXT("OMG! level is complete!"));
        GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
        DoorMeshComponent->SetMaterial(0, EnabledMaterial);
    }
}

void ADoorActor::Tick(float DeltaTime)
{
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    SetActorRotation(NewRotation);
}

void ADoorActor::EnableAllTiles()
{
    for (AActor* Tile : Tiles)
    {
        ATileActor* TileActor = Cast<ATileActor>(Tile);
        if (TileActor)
        {
            TileActor->SetEnabled();
            EnabledTiles.Add(TileActor);
        }
    }
}

bool ADoorActor::CheckEnabled()
{
    for (AActor* Tile : Tiles)
    {
        ATileActor* TileActor = Cast<ATileActor>(Tile);
        if (TileActor && TileActor->GetState() == ETileState::Enabled)
        {
            return true;
        }
    }
    return false;
}



