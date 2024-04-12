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

void ACustomGameModeBase::Respawn(AController* ControllerRef)
{
	if (ControllerRef != nullptr)
		RestartPlayer(ControllerRef);
}

void ACustomGameModeBase::RestartPlayer(AController* NewPlayer)
{
	Super::RestartPlayer(NewPlayer);
}

void ACustomGameModeBase::PlayerDied(ACharacter* Character)
{
	//Get a reference to our Character's Player Controller	
	UWorld* World = GetWorld();
	if (World != nullptr)
	{
		AController* CharacterController = Character->GetController();		
		FTimerHandle TimerHandle;
		FTimerDelegate TimerDelegate;		
		TimerDelegate.BindUFunction(this, "Respawn", CharacterController);
		World->GetTimerManager().SetTimer(TimerHandle, TimerDelegate, RespawnTime, false);		
	}
}