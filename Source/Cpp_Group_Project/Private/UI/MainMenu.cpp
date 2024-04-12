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
		StartGame_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::StartGame);

	if (SettingsMenu != nullptr)
		SettingsMenu->SetVisibility(ESlateVisibility::Collapsed);

	if (ExitGame_btn != nullptr)
		ExitGame_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::ExitGame);

	if (OptionsMenu_btn != nullptr)
		OptionsMenu_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::OpenSettings);

	if (CloseOptionsMenu_btn != nullptr)
		CloseOptionsMenu_btn->OnClicked.AddUniqueDynamic(this, &UMainMenu::CloseSettings);
}
void UMainMenu::StartGame()
{
	// Load the desired map
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("Level1"));
}
void UMainMenu::OpenSettings()
{	
	if (SettingsMenu != nullptr)
		SettingsMenu->SetVisibility(ESlateVisibility::Visible);	
}

void UMainMenu::CloseSettings()
{	
	if (SettingsMenu != nullptr)
		SettingsMenu->SetVisibility(ESlateVisibility::Collapsed);	
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