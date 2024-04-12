// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/UIPlayerController.h"

void AUIPlayerController::BeginPlay()
{
	bShowMouseCursor = true;
	bEnableClickEvents = true;
	bEnableMouseOverEvents = true;
	SetInputMode(FInputModeUIOnly());
}
