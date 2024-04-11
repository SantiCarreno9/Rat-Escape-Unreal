// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenu.generated.h"
class UOverlay;
class UButton;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UPauseMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> PauseMenu_overlay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> Resume_btn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> MainMenu_btn;

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:
	UFUNCTION()
	void BackToMainMenu();
	
};
