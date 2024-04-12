// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Components/Overlay.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Character/CustomPlayerController.h"

void UPauseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (ResumeButton != nullptr)
	{
		ResumeButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::ResumeGame);
	}
	if (MainMenuButton != nullptr)
	{
		MainMenuButton->OnClicked.AddUniqueDynamic(this, &UPauseMenu::GoToMainMenu);
	}

	CloseMenu();

	ControllerRef = Cast<ACustomPlayerController>(GetOwningPlayer());
	if (ControllerRef != nullptr)
		ControllerRef->OnPaused.AddDynamic(this, &UPauseMenu::ToggleMenu);

}

void UPauseMenu::OpenMenu()
{
	if (ControllerRef != nullptr)
		ControllerRef->bShowMouseCursor = true;
	MenuContainer->SetVisibility(ESlateVisibility::Visible);
}

void UPauseMenu::CloseMenu()
{
	MenuContainer->SetVisibility(ESlateVisibility::Collapsed);
	if (ControllerRef != nullptr)
		ControllerRef->bShowMouseCursor = false;
}

void UPauseMenu::ResumeGame()
{
	if (ControllerRef != nullptr)
		ControllerRef->PauseGame();
}

void UPauseMenu::GoToMainMenu()
{	
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}

void UPauseMenu::ToggleMenu(bool Open)
{
	if (Open) OpenMenu();
	else CloseMenu();
}
