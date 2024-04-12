// Fill out your copyright notice in the Description page of Project Settings.


#include "Observer/GameObserverActor.h"

// Sets default values
AGameObserverActor::AGameObserverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AGameObserverActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AGameObserverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

