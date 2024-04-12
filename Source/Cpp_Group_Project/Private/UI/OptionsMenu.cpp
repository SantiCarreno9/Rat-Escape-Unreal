// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OptionsMenu.h"

#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/Slider.h"
#include <UI/HUDMainMenu.h>

void UOptionsMenu::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UOptionsMenu::NativeConstruct()
{
	Super::NativeConstruct();
	
	if (OptionsMenu_overlay != nullptr)
	{
		OptionsMenu_overlay->SetVisibility(ESlateVisibility::Visible);
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