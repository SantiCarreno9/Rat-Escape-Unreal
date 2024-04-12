// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDUIOnly.generated.h"

/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API AHUDUIOnly : public AHUD
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;
	
protected:

	//--------METHODS--------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

};
