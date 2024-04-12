// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "EndingWidget.generated.h"

class UButton;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UEndingWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadWrite, meta = (AllowPrivateAccess = "true", BindWidget))
	TObjectPtr<UButton> MainMenuBtn;

	UFUNCTION()
	void GoToMainMenu();

protected:
	virtual void NativeConstruct() override;

	virtual void NativePreConstruct() override;

};
