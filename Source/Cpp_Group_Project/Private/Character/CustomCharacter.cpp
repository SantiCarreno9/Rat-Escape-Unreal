// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomCharacter.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Character/Weapon.h"
#include "Components/ChildActorComponent.h"

// Sets default values
ACustomCharacter::ACustomCharacter()
{
	// Create a first person camera component.
	CameraComponent = CreateDefaultSubobject<UCameraComponent>(TEXT("CameraComponent"));
	CameraComponent->SetupAttachment(GetMesh(), TEXT("Head"));

	//// Enable the pawn to control camera rotation.
	CameraComponent->bUsePawnControlRotation = true;

	WeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponActor->SetupAttachment(GetMesh(), TEXT("b_WeaponSocket"));
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<AWeapon>(WeaponActor->GetChildActor());
	//GetMesh()->HideBoneByName(HeadBoneName, EPhysBodyOp::PBO_None);
}

void ACustomCharacter::Move(FVector2D Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector ForwardDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
	AddMovementInput(ForwardDirection, Value.Y);
	AddMovementInput(RightDirection, Value.X);
	UE_LOG(LogTemp, Warning, TEXT("X: %f - Y: %f"), Value.X, Value.Y);
}

void ACustomCharacter::Look_Implementation(FVector2D Value)
{
	AddControllerYawInput(Value.X);
	AddControllerPitchInput(Value.Y);
}

void ACustomCharacter::Fire()
{
	if (Weapon != nullptr)
		Weapon->Fire();
}

