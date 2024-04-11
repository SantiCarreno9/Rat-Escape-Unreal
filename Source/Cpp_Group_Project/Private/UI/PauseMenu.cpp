// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/PauseMenu.h"
#include "Components/Overlay.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"

void UPauseMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UPauseMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (PauseMenu_overlay != nullptr)
	{
		PauseMenu_overlay->SetVisibility(ESlateVisibility::Visible);
	}
	if (MainMenu_btn != nullptr)
	{
		MainMenu_btn->OnClicked.AddUniqueDynamic(this, &UPauseMenu::BackToMainMenu);
	}
	if (Resume_btn != nullptr)
	{

	}
}

void UPauseMenu::BackToMainMenu()
{
	// Load the desired map
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
