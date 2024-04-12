// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CharacterHUD.generated.h"

class UHUDWidget;
class UPauseMenu;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API ACharacterHUD : public AHUD
{
	GENERATED_BODY()	
	
	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UHUDWidget> WidgetClass;

	TObjectPtr<UHUDWidget> HUDWidget;

	UPROPERTY(EditAnywhere, Category = Widget, BlueprintReadWrite, meta = (AllowPrivateAccess = "true"))
	TSubclassOf<UPauseMenu> PauseMenuClass;

	TObjectPtr<UPauseMenu> PauseMenu;

protected:
	//--------METHODS--------
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	void ShowFPSHUD();

	void HideFPSHUD();
};
