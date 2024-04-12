// Fill out your copyright notice in the Description page of Project Settings.


#include "UI/EndingWidget.h"
#include <Kismet/GameplayStatics.h>
#include "Components/Button.h"

void UEndingWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

}

void UEndingWidget::NativeConstruct()
{
	Super::NativeConstruct();

	if (MainMenuBtn != nullptr)
	{
		MainMenuBtn->OnClicked.AddUniqueDynamic(this, &UEndingWidget::GoToMainMenu);
	}

}

void UEndingWidget::GoToMainMenu()
{
	UGameplayStatics::OpenLevel(GetWorld(), TEXT("MainMenu"));
}
