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
	currentBatCount = 0;
	timeAccumulator = 0;
}

// Called every frame
void ABatSpawner::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (batBPToSpawn == nullptr) 
	{
		return;
	}
	if (currentBatCount >= maxBatCount)
	{
		return;
	}
	timeAccumulator += DeltaTime;
	if (timeAccumulator >= spawnPerSecond) 
	{
		timeAccumulator = 0;		
		currentBatCount++;
		FVector location = GetActorLocation();
		float offsetX = FMath::RandRange(-spawnAreaSize / 2, spawnAreaSize / 2);
		float offsetY = FMath::RandRange(-spawnAreaSize / 2, spawnAreaSize / 2);
		FVector spawnLocation = location + FVector(offsetX, offsetY, 0);
		ABat* bat = GetWorld()->SpawnActor<ABat>(batBPToSpawn, spawnLocation, FRotator::ZeroRotator);
		bat->InjectSpawner(this);
		bat->SetDestination(GetRandomTile());
	}
}

ATileActor* ABatSpawner::GetRandomTile()
{
	return (ATileActor*)door->Tiles[FMath::RandRange(0, door->Tiles.Num() - 1)];
}

