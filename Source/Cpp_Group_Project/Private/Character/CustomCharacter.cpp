// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/Weapon.h"
#include "Components/ChildActorComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Character/CharacterHUD.h"
#include "General/CustomGameModeBase.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
	//FIRST PERSON
	// 
	// Create a first person camera component.
	FPSCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	FPSCameraComponent->SetupAttachment(GetMesh(), TEXT("Neck"));
	FPSCameraComponent->bEditableWhenInherited = true;
	FPSCameraComponent->bAutoActivate = false;

	//// Enable the pawn to control camera rotation.
	FPSCameraComponent->bUsePawnControlRotation = true;

	WeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponActor->SetupAttachment(GetMesh(), TEXT("b_WeaponSocket"));


	////THIRD PERSON
	//// Create a camera boom...
	TPCameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("TPCameraBoom"));
	TPCameraBoom->SetupAttachment(RootComponent);
	TPCameraBoom->SetUsingAbsoluteRotation(true);
	TPCameraBoom->bUsePawnControlRotation = true;
	TPCameraBoom->TargetArmLength = 300.f;
	TPCameraBoom->SetRelativeRotation(FRotator(-60.f, 0.f, 0.f));


	//// Create a camera...
	TPCameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("ThirdPersonCamera"));
	TPCameraComponent->SetupAttachment(TPCameraBoom, USpringArmComponent::SocketName);
	TPCameraComponent->bUsePawnControlRotation = false; // Camera does not rotate relative to arm
	TPCameraComponent->bAutoActivate = true;

	//// Create dummy weapon
	BackWeapon = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BackWeapon"));
	BackWeapon->SetupAttachment(GetMesh(), TEXT("b_BackWeaponSocket"));
}



// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<AWeapon>(WeaponActor->GetChildActor());
	SwitchToNormalMode();
}

#pragma region Player Input

void ACustomCharacter::Move(FVector2D Value)
{
	// find out which way is forward
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0, Rotation.Yaw, 0);

	// get forward vector
	const FVector ForwardDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);

	// get right vector 
	const FVector RightDirection = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);

	// add movement 
	AddMovementInput(ForwardDirection, Value.Y);
	AddMovementInput(RightDirection, Value.X);
}

void ACustomCharacter::Look(FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ACustomCharacter::Fire()
{
	if (bIsOnAttackMode && Weapon != nullptr)
		Weapon->Fire();
}

#pragma endregion

#pragma region Perspective

void ACustomCharacter::SwitchCamera()
{
	if (bIsOnThirdPersonView)
		SwitchToFirstPersonPerspective();
	else SwitchToThirdPersonPerspective();
}

void ACustomCharacter::SwitchToFirstPersonPerspective()
{
	bIsOnThirdPersonView = false;
	FPSCameraComponent->SetActive(!bIsOnThirdPersonView);
	TPCameraComponent->SetActive(bIsOnThirdPersonView);
	GetMesh()->HideBoneByName(HeadBoneName, EPhysBodyOp::PBO_None);
	if (bIsOnAttackMode && CharacterHUD != nullptr)
		CharacterHUD->ShowFPSHUD();
}

void ACustomCharacter::SwitchToThirdPersonPerspective()
{
	bIsOnThirdPersonView = true;
	FPSCameraComponent->SetActive(!bIsOnThirdPersonView);
	TPCameraComponent->SetActive(bIsOnThirdPersonView);
	GetMesh()->UnHideBoneByName(HeadBoneName);
	if (bIsOnAttackMode && CharacterHUD != nullptr)
		CharacterHUD->HideFPSHUD();
}

void ACustomCharacter::Falling()
{
	if (!bIsOnThirdPersonView)
		SwitchToThirdPersonPerspective();
}

#pragma endregion


#pragma region Mode

void ACustomCharacter::SwitchMode()
{
	if (bIsOnAttackMode)
		SwitchToNormalMode();
	else SwitchToAttackMode();
}

void ACustomCharacter::SwitchToAttackMode()
{
	bIsOnAttackMode = true;
	BackWeapon->SetVisibility(false);
	if (Weapon != nullptr)
		Weapon->SetActorHiddenInGame(false);
	if (!bIsOnThirdPersonView && CharacterHUD != nullptr)
		CharacterHUD->ShowFPSHUD();

}

void ACustomCharacter::SwitchToNormalMode()
{
	bIsOnAttackMode = false;
	BackWeapon->SetVisibility(true);
	if (Weapon != nullptr)
		Weapon->SetActorHiddenInGame(true);
	if (!bIsOnThirdPersonView && CharacterHUD != nullptr)
		CharacterHUD->HideFPSHUD();
}

void ACustomCharacter::SetControllerRef(APlayerController* PController)
{
	PlayerController = PController;
	CharacterHUD = Cast<ACharacterHUD>(PlayerController->GetHUD());
}

#pragma endregion


void ACustomCharacter::Destroyed()
{
	if (UWorld* World = GetWorld())
	{
		if (ACustomGameModeBase* GameMode = Cast<ACustomGameModeBase>(World->GetAuthGameMode()))
		{
			if (GameMode->GetOnPlayerDied().IsBound())
				GameMode->GetOnPlayerDied().Broadcast(this);
		}
	}
	Super::Destroyed();
}
