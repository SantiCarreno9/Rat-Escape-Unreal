// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MainMenu.generated.h"
class UOverlay;
class UButton;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UMainMenu : public UUserWidget
{

	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UOverlay> MainMenu_overlay;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> StartGame_btn;
	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> ExitGame_btn;

	
	

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

public:
	UFUNCTION()
	void StartGame();
	UFUNCTION()
	void ExitGame();

};
