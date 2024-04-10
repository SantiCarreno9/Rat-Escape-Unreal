// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OptionsMenu.h"

#include "Components/Overlay.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"
#include "Components/Slider.h"

void UOptionsMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenu_btn != nullptr)
	{
		MainMenu_btn->OnClicked.AddUniqueDynamic(this, &UOptionsMenu::BackToMainMenu);
	}
	if (MasterVolume_slider != nullptr)
	{
		MasterVolume_slider->OnValueChanged.AddDynamic(this, &UOptionsMenu::SetMasterVolume);
	}
	if (EffectsVolume_slider != nullptr)
	{
		EffectsVolume_slider->OnValueChanged.AddDynamic(this, &UOptionsMenu::SetEffectsVolume);
	}
	if (BackgroundVolume_slider != nullptr)
	{
		BackgroundVolume_slider->OnValueChanged.AddDynamic(this, &UOptionsMenu::SetBackgroundVolume);
	}
}
void UOptionsMenu::BackToMainMenu()
{
	// Load the desired map
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
void UOptionsMenu::SetMasterVolume(float Volume)
{
	// Set master volume here using Volume parameter
}
void UOptionsMenu::SetBackgroundVolume(float Volume)
{
	// Set Background volume here using Volume parameter
}
void UOptionsMenu::SetEffectsVolume(float Volume)
{
	// Set effects volume here using Volume parameter
}