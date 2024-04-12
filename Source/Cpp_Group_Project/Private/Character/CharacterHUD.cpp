// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CharacterHUD.h"
#include "Blueprint/UserWidget.h"
#include "Character/HUDWidget.h"
#include "UI/PauseMenu.h"

void ACharacterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr)
	{
		HUDWidget = CreateWidget<UHUDWidget>(GetWorld(), WidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass != nullptr"));		
		if (HUDWidget)
		{
			HUDWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Added to Viewport"));
		}
	}

	if (PauseMenuClass != nullptr)
	{
		PauseMenu = CreateWidget<UPauseMenu>(GetWorld(), PauseMenuClass);
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass != nullptr"));
		if (PauseMenu)
		{
			PauseMenu->AddToViewport();			
			UE_LOG(LogTemp, Warning, TEXT("Added to Viewport"));
		}
	}
	
}

void ACharacterHUD::ShowFPSHUD()
{
	if (HUDWidget != nullptr)	
		HUDWidget->ShowFPSHUD();	
}

void ACharacterHUD::HideFPSHUD()
{
	if (HUDWidget != nullptr)
		HUDWidget->HideFPSHUD();
}
