// Fill out your copyright notice in the Description page of Project Settings.


#include "GameObserverActor.h"
#include <Kismet/GameplayStatics.h>

// Sets default values
AGameObserverActor::AGameObserverActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

}

// Called when the game starts or when spawned
void AGameObserverActor::BeginPlay()
{
	Super::BeginPlay();

	TArray<AActor*> FoundActors;
	UGameplayStatics::GetAllActorsWithTag(GetWorld(), "Door", FoundActors);

	for (AActor* FoundActor : FoundActors) {
		FlagMessage();
		ADoorActor* Door = Cast<ADoorActor>(FoundActor);
		Door->OnDoorStateChanged.AddDynamic(this, &AGameObserverActor::OnDoorStateChanged);
	}
	
	
}

void AGameObserverActor::OnDoorStateChanged(ADoorActor* Door)
{
	FlagMessage();
	FString DebugMessage = FString::Printf(TEXT("Door state change detected"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
}



// Called every frame
void AGameObserverActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AGameObserverActor::FlagMessage() {
	FString DebugMessage = FString::Printf(TEXT("FlaggedObserver"));
	GEngine->AddOnScreenDebugMessage(-1, 5.0f, FColor::Yellow, DebugMessage);
}