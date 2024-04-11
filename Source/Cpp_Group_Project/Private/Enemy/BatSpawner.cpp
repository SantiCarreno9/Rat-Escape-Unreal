// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/BatSpawner.h"
#include "Enemy/Bat.h"

// Sets default values
ABatSpawner::ABatSpawner()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ABatSpawner::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ABatSpawner::Tick(float DeltaTime)
{
	if (batBPToSpawn == nullptr) 
	{
		return;
	}
	Super::Tick(DeltaTime);
	timeAccumulator += DeltaTime;
	if (timeAccumulator >= spawnPerSecond) 
	{
		timeAccumulator = 0;
		FVector location = GetActorLocation();
		float offsetX = FMath::RandRange(-spawnAreaSize / 2, spawnAreaSize / 2);
		float offsetY = FMath::RandRange(-spawnAreaSize / 2, spawnAreaSize / 2);
		FVector spawnLocation = location + FVector(offsetX, offsetY, 0);
		ABat* bat = GetWorld()->SpawnActor<ABat>(batBPToSpawn, spawnLocation, FRotator::ZeroRotator);
		bat->SetDestination(FVector(0, 0, 0));
	}
}

