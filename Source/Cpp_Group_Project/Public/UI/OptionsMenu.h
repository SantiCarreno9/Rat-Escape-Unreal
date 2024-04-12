// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OptionsMenu.generated.h"
class UOverlay;
class UButton;
class USlider;
/**
 *
 */
UCLASS()
class CPP_GROUP_PROJECT_API UOptionsMenu : public UUserWidget
{
	GENERATED_BODY()
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> OptionsMenu_overlay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<USlider> MasterVolume_slider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<USlider> BackgroundVolume_slider;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<USlider> EffectsVolume_slider;

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:
	UFUNCTION()
	void SetMasterVolume(float Volume);
	UFUNCTION()
	void SetBackgroundVolume(float Volume);
	UFUNCTION()
	void SetEffectsVolume(float Volume);
};
