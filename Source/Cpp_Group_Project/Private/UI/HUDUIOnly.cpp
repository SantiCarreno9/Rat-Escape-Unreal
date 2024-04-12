// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDUIOnly.h"
#include "Blueprint/UserWidget.h"

void AHUDUIOnly::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr)
	{
		UUserWidget* Instance = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		if (Instance)		
			Instance->AddToViewport();		
	}
}
