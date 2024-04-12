// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomPlayerController.h"
#include "Character/CustomCharacter.h"
#include "EnhancedInputComponent.h"
#include "InputActionValue.h"
#include "EnhancedInputSubsystems.h"

void ACustomPlayerController::BeginPlay()
{
	//Add Input Mapping Context
	if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		Subsystem->AddMappingContext(MappingContext, 0);
	}

	SetInputMode(FInputModeGameOnly());
}

void ACustomPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	// Set up action bindings
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(InputComponent))
	{
		//Movement Bindings
		EnhancedInputComponent->BindAction(MoveAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Move);
		//Look Bindings
		EnhancedInputComponent->BindAction(LookAction, ETriggerEvent::Triggered, this, &ACustomPlayerController::Look);
		//Fire Bindings
		EnhancedInputComponent->BindAction(FireAction, ETriggerEvent::Started, this, &ACustomPlayerController::Fire);
		//Camera Bindings
		EnhancedInputComponent->BindAction(SwitchCameraAction, ETriggerEvent::Started, this, &ACustomPlayerController::SwitchCamera);
		//Mode Bindings
		EnhancedInputComponent->BindAction(SwitchModeAction, ETriggerEvent::Started, this, &ACustomPlayerController::SwitchMode);

		//Extra Bindings
		EnhancedInputComponent->BindAction(PauseAction, ETriggerEvent::Started, this, &ACustomPlayerController::PauseGame);
	}
}

void ACustomPlayerController::OnPossess(APawn* aPawn)
{
	Super::OnPossess(aPawn);
	Character = Cast<ACustomCharacter>(aPawn);
	Character->SetControllerRef(this);
}

void ACustomPlayerController::OnUnPossess()
{
	Super::OnUnPossess();
	Character = nullptr;
}

void ACustomPlayerController::Move(const FInputActionValue& Value)
{
	if (Character != nullptr)
		Character->Move(Value.Get<FVector2D>());
}

void ACustomPlayerController::Look(const FInputActionValue& Value)
{
	if (Character != nullptr)
		Character->Look(Value.Get<FVector2D>());
}

void ACustomPlayerController::Fire()
{
	if (Character != nullptr)
		Character->Fire();
}

void ACustomPlayerController::SwitchCamera()
{
	if (Character != nullptr)
		Character->SwitchCamera();
}

void ACustomPlayerController::SwitchMode()
{
	if (Character != nullptr)
		Character->SwitchMode();
}

void ACustomPlayerController::PauseGame()
{
	bool Pause = !IsPaused();
	SetPause(Pause);
	if (Pause) SetInputMode(FInputModeUIOnly());
	else SetInputMode(FInputModeGameOnly());
	OnPaused.Broadcast(Pause);
}