// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HUDWidget.generated.h"

class UOverlay;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UHUDWidget : public UUserWidget
{
	GENERATED_BODY()	

	bool bIsTutorialOpen = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FPS, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> FPS;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FPS, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> TutorialScreen;

	UFUNCTION()
	void ToggleTutorial();

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:

	void ShowFPSHUD();

	void HideFPSHUD();

	void ShowTutorial();

	void HideTutorial();
};
