// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDOptionsMenu.h"
#include "Blueprint/UserWidget.h"


void AHUDOptionsMenu::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr)
	{
		OptionsMenuWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass != nullptr"));
		if (OptionsMenuWidget)
		{
			OptionsMenuWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Added to Viewport"));
		}
	}
}