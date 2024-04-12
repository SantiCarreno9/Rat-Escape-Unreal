// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "BatSpawner.generated.h"

UCLASS()
class CPP_GROUP_PROJECT_API ABatSpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ABatSpawner();
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	int spawnPerSecond;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float spawnAreaSize;
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	TSubclassOf<AActor> batBPToSpawn;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

private:	
	float timeAccumulator;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
