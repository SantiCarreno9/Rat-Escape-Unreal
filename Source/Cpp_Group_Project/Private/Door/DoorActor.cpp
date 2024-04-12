// Fill out your copyright notice in the Description page of Project Settings.


#include "Door/DoorActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
ADoorActor::ADoorActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    RootComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));

    DoorMeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    DoorMeshComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoorActor::OnOverlapStart);
    DoorMeshComponent->SetupAttachment(RootComponent);

    USceneComponent* PortalRoot = CreateDefaultSubobject<USceneComponent>(TEXT("PortalRoot"));
    PortalRoot->SetupAttachment(RootComponent);

    basePortalDoor = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BaseMesh"));
    basePortalDoor->SetupAttachment(PortalRoot);

    invisibleStep = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("InvisibleStep"));
    invisibleStep->SetupAttachment(RootComponent);

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
    DoorMeshComponent->SetHiddenInGame(true);
    DoorMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

    StartLevel(LevelIndex++);
}

void ADoorActor::OnOverlapStart(
    UPrimitiveComponent* OverlappedComponent, 
    AActor* OtherActor, 
    UPrimitiveComponent* OtherComp, 
    int32 OtherBodyIndex, 
    bool bFromSweep, 
    const FHitResult& SweepResult)
{
    if (OtherActor && OtherActor->IsA<ACustomCharacter>())
    {
        //FlagMessage();
        DoorMeshComponent->SetHiddenInGame(true);
        DoorMeshComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
        SetDoorState(EDoorState::Filled);
        // Reactivate all the tiles
        for (AActor* Tile : Tiles) {
            Cast<ATileActor>(Tile)->TileState = ETileState::Enabled;
            Cast<ATileActor>(Tile)->SetEnabled();
            Tile->SetActorHiddenInGame(false);
            Tile->SetActorEnableCollision(true);
        }
        // next level call
        StartLevel(LevelIndex++);

        // Refill the enabledtiles array
        for (AActor* TTile : Tiles) {
            ATileActor* Tile = Cast<ATileActor>(TTile);
            if (Tile->GetState() == ETileState::Enabled)
            {
                EnabledTiles.Add(Tile);
            }
        }
        
    }
}

void ADoorActor::HandleTileStateChanged(ATileActor* Tile)
{
    //FlagMessage();
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
        DoorMeshComponent->SetHiddenInGame(false);
        DoorMeshComponent->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
        DoorMeshComponent->SetMaterial(0, EnabledMaterial);
    }
}

void ADoorActor::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);

    FRotator NewRotation = DoorMeshComponent->GetComponentRotation();
    NewRotation.Yaw += RotationSpeed * DeltaTime;
    DoorMeshComponent->SetWorldRotation(NewRotation);
}

void ADoorActor::SetDoorState(EDoorState NewDoorState)
{
    DoorState = NewDoorState;
    
    OnDoorStateChanged.Broadcast(this);
}

void ADoorActor::StartLevel(int NewLevelIndex)
{
    switch (NewLevelIndex) {
    case 0:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L1")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            }
    break;
    case 1:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L2")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            else { Cast<ATileActor>(Tile)->SetEnabled(); }
        }
        break;
    case 2:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L3")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            else { Cast<ATileActor>(Tile)->SetEnabled(); }
        }
        break;
    case 3:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L4")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            else { Cast<ATileActor>(Tile)->SetEnabled(); }
        }
        break;
    case 4:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L5")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            else { Cast<ATileActor>(Tile)->SetEnabled(); }
        }
        break;
    case 5:
        for (AActor* Tile : Tiles) {
            if (!Cast<ATileActor>(Tile)->Tags.Contains("L6")) {
                Cast<ATileActor>(Tile)->TileState = ETileState::Disabled;
                Tile->SetActorHiddenInGame(true);
                Tile->SetActorEnableCollision(false);
            }
            else { Cast<ATileActor>(Tile)->SetEnabled(); }
        }
        break;
    case 6:

        break;
    default:
        break;
    }
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

void ADoorActor::FlagMessage() {
    FString DebugMessage = FString::Printf(TEXT("Flagged"));
    GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
}



