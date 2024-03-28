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

	// Attach the camera component to our capsule component.
	CameraComponent->SetupAttachment(CastChecked<USceneComponent, UCapsuleComponent>(GetCapsuleComponent()));

	// Position the camera slightly above the eyes.
	CameraComponent->SetRelativeLocation(FVector(0.0f, 0.0f, 50.0f + BaseEyeHeight));

	// Enable the pawn to control camera rotation.
	CameraComponent->bUsePawnControlRotation = true;

	// Create a first person mesh component for the owning player.
	CharacterMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));

	// Only the owning player sees this mesh.
	CharacterMesh->SetOnlyOwnerSee(true);

	// Attach the FPS mesh to the FPS camera.
	CharacterMesh->SetupAttachment(CameraComponent);

	// Disable some environmental shadows to preserve the illusion of having a single mesh.
	CharacterMesh->bCastDynamicShadow = false;
	CharacterMesh->CastShadow = false;

	// The owning player doesn't see the regular (third-person) body mesh.
	GetMesh()->SetOwnerNoSee(true);

	WeaponActor = CreateDefaultSubobject<UChildActorComponent>(TEXT("Weapon"));
	WeaponActor->SetupAttachment(GetMesh(), TEXT("b_WeaponSocket"));
}

// Called when the game starts or when spawned
void ACustomCharacter::BeginPlay()
{
	Super::BeginPlay();
	Weapon = Cast<AWeapon>(WeaponActor->GetChildActor());
}

void ACustomCharacter::Move(FVector2D Value)
{
	// Find out which way is "forward" and record that the player wants to move that way.
	FVector ForwardDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::X);
	FVector RightDirection = FRotationMatrix(Controller->GetControlRotation()).GetScaledAxis(EAxis::Y);
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
	if (Weapon != nullptr)
		Weapon->Fire();
}

