// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/OptionsMenu.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Overlay.h"
#include "Components/Button.h"
#include "Components/Slider.h"

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
	SetBackgroundVolume(Volume);
	SetEffectsVolume(Volume);
	// Set master volume here using Volume parameter
}
void UOptionsMenu::SetBackgroundVolume(float Volume)
{	
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixRef, MusicSoundClass, Volume);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixRef);
}
void UOptionsMenu::SetEffectsVolume(float Volume)
{
	UGameplayStatics::SetSoundMixClassOverride(GetWorld(), SoundMixRef, SFXSoundClass, Volume);
	UGameplayStatics::PushSoundMixModifier(GetWorld(), SoundMixRef);
}