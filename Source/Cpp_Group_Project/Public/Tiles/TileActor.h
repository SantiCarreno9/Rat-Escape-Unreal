// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Components/StaticMeshComponent.h"
#include <Character/CustomCharacter.h>
#include "TileActor.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FStateChangedDelegate, ATileActor*, Tile);

UENUM(BlueprintType)
enum class ETileState : uint8
{
	Enabled,
	Disabled,
	SteppedOn
};

UCLASS()
class CPP_GROUP_PROJECT_API ATileActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATileActor();

	ETileState GetState() const { return TileState; }

	TArray<ATileActor*> GetNeighbors() const;

	void SetEnabled();

	void SetDisabled();

	void SteppedOn();

	UPROPERTY(BlueprintAssignable, Category = "Tile")
	FStateChangedDelegate OnStateChanged;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, Category = "TileLogic")
	UStaticMeshComponent* TileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "TileLogic")
	UStaticMeshComponent* invisibleTileMeshComponent;

	UPROPERTY(VisibleAnywhere, Category = "TileLogic")
	TArray<ATileActor*> Neighbors;

	UPROPERTY(EditAnywhere, Category = "TileLogic")
	TArray<UMaterialInterface*> TileMaterials;

	UFUNCTION()
	void FindNeighbors();

	// this function is the "oncollision enter"
	UFUNCTION()
	void OnTileOverlap(
		UPrimitiveComponent* OverlappedComponent,
		AActor* OtherActor,
		UPrimitiveComponent* OtherComp,
		int32 OtherBodyIndex,
		bool bFromSweep,
		const FHitResult& SweepResult);

public:	
	// Called every frame
	//virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, Category = "TileLogic")
	ETileState TileState;


};
