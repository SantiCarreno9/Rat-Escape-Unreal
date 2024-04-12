// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Door/DoorActor.h"
#include "GameObserverActor.generated.h"

UCLASS()
class CPP_GROUP_PROJECT_API AGameObserverActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGameObserverActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Function to handle door state change
	void OnDoorStateChanged(ADoorActor* NewState);

private:
	// blueprints of the logic levels
	UPROPERTY(EditAnywhere)
	TArray<TSubclassOf<AActor>> BlueprintsToDestroyAndLoad;

	UPROPERTY(EditAnywhere)
	ADoorActor* DoorBP;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FlagMessage();

};
