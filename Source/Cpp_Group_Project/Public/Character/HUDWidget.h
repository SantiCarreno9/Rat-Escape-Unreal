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

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, Category = FPS, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> FPS;

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:

	void ShowFPSHUD();

	void HideFPSHUD();
};
