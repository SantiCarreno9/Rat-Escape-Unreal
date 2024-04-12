// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PauseMenuWidget.generated.h"

class UOverlay;
class UButton;
class ACustomPlayerController;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UPauseMenuWidget : public UUserWidget
{
	GENERATED_BODY()	

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> MenuContainer;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> ResumeButton;

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> MainMenuButton;

	TObjectPtr<ACustomPlayerController> ControllerRef;

	UFUNCTION()
	void ResumeGame();

	UFUNCTION()
	void GoToMainMenu();

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:
	
	void OpenMenu();

	void CloseMenu();
};
