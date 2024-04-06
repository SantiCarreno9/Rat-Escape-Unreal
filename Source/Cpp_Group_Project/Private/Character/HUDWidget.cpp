// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HUDWidget.h"
#include "Components/Overlay.h"

void UHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	HideFPSHUD();
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
}

void UHUDWidget::ShowFPSHUD()
{
	if (FPS != nullptr)
		FPS->SetVisibility(ESlateVisibility::Visible);
}

void UHUDWidget::HideFPSHUD()
{
	if (FPS != nullptr)
		FPS->SetVisibility(ESlateVisibility::Hidden);
}
