// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/HUDWidget.h"
#include "Components/Overlay.h"
#include "Character/CustomPlayerController.h"

void UHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	HideFPSHUD();
}

void UHUDWidget::ToggleTutorial()
{
	if (bIsTutorialOpen)HideTutorial();
	else ShowTutorial();
	bIsTutorialOpen = !bIsTutorialOpen;
}

void UHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();
	
	ACustomPlayerController* ControllerRef = Cast<ACustomPlayerController>(GetOwningPlayer());
	if (ControllerRef != nullptr)
		ControllerRef->OnTutorialAction.AddDynamic(this, &UHUDWidget::ToggleTutorial);
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

void UHUDWidget::ShowTutorial()
{
	if(TutorialScreen!=nullptr)
		TutorialScreen->SetVisibility(ESlateVisibility::Visible);
}

void UHUDWidget::HideTutorial()
{
	if (TutorialScreen != nullptr)
		TutorialScreen->SetVisibility(ESlateVisibility::Hidden);
}
