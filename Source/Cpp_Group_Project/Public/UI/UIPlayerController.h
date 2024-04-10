// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "UIPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API AUIPlayerController : public APlayerController
{
	GENERATED_BODY()
	
protected:
	//--------METHODS--------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
