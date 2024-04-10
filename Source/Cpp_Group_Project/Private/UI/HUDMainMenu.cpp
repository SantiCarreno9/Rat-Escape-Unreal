// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/HUDMainMenu.h"
#include "Blueprint/UserWidget.h"
#include "GameFramework/PlayerController.h"

void AHUDMainMenu::BeginPlay()
{
	Super::BeginPlay();

	if (WidgetClass != nullptr)
	{
		MainMenuWidget = CreateWidget<UUserWidget>(GetWorld(), WidgetClass);
		UE_LOG(LogTemp, Warning, TEXT("WidgetClass != nullptr"));
		if (MainMenuWidget)
		{
			MainMenuWidget->AddToViewport();
			UE_LOG(LogTemp, Warning, TEXT("Added to Viewport"));	
		}
	}
	
	//APlayerController* Controller = GetOwningPlayerController();
	//if (Controller != nullptr)
	//{
	//	Controller->bShowMouseCursor = true;
	//	Controller->bEnableClickEvents = true;
	//	Controller->bEnableMouseOverEvents = true;
	//}
}