// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Bat.generated.h"

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
	FVector destination;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void SetDestination(FVector target);
};
