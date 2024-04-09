// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDOptionsMenu.generated.h"

/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API AHUDOptionsMenu : public AHUD
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;
	// Reference to the created widget instance
	UUserWidget* OptionsMenuWidget;

	//--------METHODS--------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
};
