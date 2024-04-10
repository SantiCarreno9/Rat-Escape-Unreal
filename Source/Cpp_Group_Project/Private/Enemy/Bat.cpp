// Fill out your copyright notice in the Description page of Project Settings.


#include "Enemy/Bat.h"

// Sets default values
ABat::ABat()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	USkeletalMeshComponent* skeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	skeletalMeshComponent->SetupAttachment(RootComponent);
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> skeletalMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/Art/Character/Mouse/Rat.Rat'"));
	if (skeletalMesh.Succeeded()) 
	{
		skeletalMeshComponent->SetSkeletalMesh(skeletalMesh.Object);
	}
}

// Called when the game starts or when spawned
void ABat::BeginPlay()
{
	Super::BeginPlay();
	SetDestination(TestDestination);	
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
	FVector direction = destination - position;
	if (direction.Length() > 10) 
	{
		direction.Normalize();
		position += Speed * DeltaTime * direction;
		SetActorLocation(position);
		return;
	}

	//Handle logic for when bat reaches the position.
	hasDestination = false;	
}

void ABat::SetDestination(FVector target) 
{
	hasDestination = true;
	destination = target;
}

