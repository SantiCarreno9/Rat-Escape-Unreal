// Fill out your copyright notice in the Description page of Project Settings.


#include "General/CustomGameModeBase.h"
#include "Character/CustomCharacter.h"
#include "UObject/ConstructorHelpers.h"

void ACustomGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//Bind our Player died delegate to the Gamemode's PlayerDied function.
	if (!OnPlayerDied.IsBound())
	{
		OnPlayerDied.AddDynamic(this, &ACustomGameModeBase::PlayerDied);
	}
}

void ACustomGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);	
}

void ACustomGameModeBase::PlayerDied(ACharacter* Character)
{
	UE_LOG(LogTemp, Warning, TEXT("Character %s"), *Character->GetName());
	//Get a reference to our Character's Player Controller
	AController* CharacterController = Character->GetController();

	TFunction<void()> OnDelayLambda = [this, CharacterController]() {
		RestartPlayer(CharacterController);		
		};
	FTimerHandle TimerHandle;
	FTimerDelegate TimerDelegate;
	TimerDelegate.BindLambda(OnDelayLambda);
	GetWorld()->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, RespawnTime, false);
	RestartPlayer(CharacterController);	
}