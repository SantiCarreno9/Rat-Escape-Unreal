// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenuWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Components/Overlay.h"
#include "Character/CustomPlayerController.h"

void UPauseMenuWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
}

void UPauseMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::ResumeGame);
	}
	if (MainMenuButton != nullptr)
	{
		MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenuWidget::GoToMainMenu);
	}	

	ControllerRef = Cast<ACustomPlayerController>(GetOwningLocalPlayer());
}

void UPauseMenuWidget::ResumeGame()
{
	if (ControllerRef != nullptr)
		ControllerRef->SetPause(false);	
}

void UPauseMenuWidget::GoToMainMenu()
{
}

void UPauseMenuWidget::OpenMenu()
{
	MenuContainer->SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenuWidget::CloseMenu()
{
	MenuContainer->SetVisibility(ESlateVisibility::Collapsed);
}