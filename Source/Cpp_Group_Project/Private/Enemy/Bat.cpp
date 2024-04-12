// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Bat.h"
#include "Enemy/BatSpawner.h"

// Sets default values
ABat::ABat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	hasDestination = false;
	USkeletalMeshComponent* skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	skeletalMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("/Game/Art/Bat/bat.bat"));
	if (skeletalMesh.Succeeded()) 
	{
		skeletalMeshComponent->SetSkeletalMesh(skeletalMesh.Object);
		static ConstructorHelpers::FObjectFinder<UClass> animBlueprint(TEXT("Class'/Game/Art/Bat/ABP_Bat.ABP_Bat_C'"));
		if (animBlueprint.Object)
		{
			skeletalMeshComponent->SetAnimInstanceClass(animBlueprint.Object);
			skeletalMeshComponent->SetRelativeScale3D(30 * FVector(1, 1, 1));
		}
	}
}

// Called when the game starts or when spawned
void ABat::BeginPlay()
{
	Super::BeginPlay();
	initialLocation = GetActorLocation();
	//SetDestination(TestDestination);	
}

// Called every frame
void ABat::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!hasDestination) 
	{
		return;
	}
	FVector position = GetActorLocation();
	FVector direction = destination == nullptr ? initialLocation - position : destination->GetActorLocation() - position;

	if (direction.Length() > 10) 
	{
		direction.Normalize();
		position += Speed * DeltaTime * direction;
		SetActorLocation(position);
		return;
	}

	//Handle logic for when bat reaches the position.
	if (destination == nullptr)
	{
		destination = batSpawner->GetRandomTile();
	}
	else
	{
		if (destination->GetState() == ETileState::Enabled)
		{
			destination->SteppedOn();
		}
		destination = nullptr;
	}
}

void ABat::SetDestination(ATileActor* tile) 
{
	hasDestination = true;
	destination = tile;
}
void ABat::InjectSpawner(ABatSpawner* spawner)
{
	batSpawner = spawner;
}

void ABat::Kill() 
{
	batSpawner->currentBatCount--;
	Destroy();
}
