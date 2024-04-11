// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "HUDMainMenu.generated.h"

/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API AHUDMainMenu : public AHUD
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> WidgetClass;
	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UUserWidget> OptionsMenuWidgetClass;
	// Reference to the created widget instance
	UUserWidget* MainMenuWidget;
	UUserWidget* OptionsMenuWidget;

	//--------METHODS--------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
