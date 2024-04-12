// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Tiles/TileActor.h"
#include "Engine/Engine.h"
#include "DoorActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FDoorStateChanged, ADoorActor*, Door);

UENUM(BlueprintType)
enum class EDoorState : uint8
{
    Empty,
    Filled
};



UCLASS()
class CPP_GROUP_PROJECT_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorActor();

protected:
	virtual void BeginPlay() override;

    UPROPERTY(EditAnywhere, Category = "Door State")
    EDoorState DoorState;

    UPROPERTY(EditAnywhere, Category = "DoorLogic")
    UStaticMeshComponent* basePortalDoor;

    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* invisibleStep;

    // this function is the "oncollision enter"
    UFUNCTION()
    void OnOverlapStart(UPrimitiveComponent* OverlappedComponent,
        AActor* OtherActor,
        UPrimitiveComponent* OtherComp,
        int32 OtherBodyIndex,
        bool bFromSweep,
        const FHitResult& SweepResult);

public:	
    UPROPERTY(EditAnywhere)
    UStaticMeshComponent* DoorMeshComponent;

    UPROPERTY(EditAnywhere)
    TArray<AActor*> Tiles;

    UPROPERTY(EditAnywhere)
    TArray<AActor*> EnabledTiles;

    UPROPERTY(EditAnywhere)
    UMaterialInterface* EnabledMaterial;

    UPROPERTY(EditAnywhere)
    UMaterialInterface* DisabledMaterial;

    UFUNCTION()
    void HandleTileStateChanged(ATileActor* Tile);

    void EnableAllTiles();

    bool CheckEnabled();

    void FlagMessage();

    void UpdateEnabledTiles(ATileActor* ChangedTile);

    // to broadcast statechange
    UPROPERTY(BlueprintAssignable, Category = "Door State")
    FDoorStateChanged OnDoorStateChanged;

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private: 
    // Rotation speed (degrees per second)
    UPROPERTY(EditAnywhere)
    float RotationSpeed = 45.0f;

    int LevelIndex = 0;

    void SetDoorState(EDoorState NewDoorState);

    void StartLevel(int LevelIndex);
};

