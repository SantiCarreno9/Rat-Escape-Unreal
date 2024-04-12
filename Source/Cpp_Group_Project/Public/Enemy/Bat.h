// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Tiles/TileActor.h"
#include "Bat.generated.h"

class ABatSpawner;

UCLASS()
class CPP_GROUP_PROJECT_API ABat : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABat();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bat")
	float Speed = 20.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Bat")
	FVector TestDestination;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:
	bool hasDestination;
	ATileActor* destination;
	ABatSpawner* batSpawner;
	FVector initialLocation;
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void InjectSpawner(ABatSpawner* spawner);
	void SetDestination(ATileActor* tile);
	void Kill();
};
