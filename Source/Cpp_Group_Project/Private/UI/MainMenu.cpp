// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/MainMenu.h"

#include "Components/Overlay.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include <UI/HUDMainMenu.h>

void UMainMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UMainMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (StartGame_btn != nullptr)
	{
		StartGame_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::StartGame);
	}
	if (MainMenu_overlay != nullptr)
	{
		MainMenu_overlay->SetVisibility(ESlateVisibility::Visible);
	}
	if (ExitGame_btn != nullptr)
	{
		ExitGame_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::ExitGame);
	}
	if (OptionsMenu_btn != nullptr)
	{
		OptionsMenu_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OptionsMenu);
	}
}
void UMainMenu::StartGame()
{
	// Load the desired map
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level1"));
}
void UMainMenu::OptionsMenu()
{
	//Add OptionsMenuWidget to viewport and remove MainMenuWidget
	// Get the HUDMainMenu owning this widget

	AHUDMainMenu* MainMenuHUD = Cast<AHUDMainMenu>(GetOwningPlayer()->GetHUD());
	if (MainMenuHUD)
	{
		if (MainMenuHUD->OptionsMenuWidgetClass != nullptr)
		{
			UUserWidget* OptionsMenuWidget = CreateWidget<UUserWidget>(GetWorld(), MainMenuHUD->OptionsMenuWidgetClass);
			if (OptionsMenuWidget)
			{
				// Add the options menu widget to the viewport
				OptionsMenuWidget->AddToViewport();

				// Remove the main menu widget from the viewport
				if (MainMenu_overlay != nullptr)
				{
					MainMenu_overlay->SetVisibility(ESlateVisibility::Hidden);
				}
			}
		}
	}
}
void UMainMenu::ExitGame()
{
	// Quit the game
	APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
	if (PlayerController)
	{
		PlayerController->ConsoleCommand("quit");
	}
}