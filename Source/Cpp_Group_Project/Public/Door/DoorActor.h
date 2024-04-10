// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include "Tiles/TileActor.h"
#include "DoorActor.generated.h"

UCLASS()
class CPP_GROUP_PROJECT_API ADoorActor : public AActor
{
	GENERATED_BODY()
	
public:	
	ADoorActor();

protected:
	virtual void BeginPlay() override;

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

    void UpdateEnabledTiles(ATileActor* ChangedTile);

    // Called every frame
    virtual void Tick(float DeltaTime) override;

private: 
    // Rotation speed (degrees per second)
    UPROPERTY(EditAnywhere)
    float RotationSpeed = 45.0f;
};
