// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomCharacterAnimInstance.h"
#include "Character/CustomCharacter.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"

UCustomCharacterAnimInstance::UCustomCharacterAnimInstance()
{
	Pitch = 0;
	Speed = 0;
	bIsFalling = false;
}

void UCustomCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACustomCharacter>(GetOwningActor());
}

void UCustomCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;

	bIsFalling = Character->GetCharacterMovement()->IsFalling();

	if (!bIsFalling)
		Speed = Character->GetVelocity().Length();
	else Speed = 0;

	bIsOnAttackMode = Character->GetIsOnAttackMode();

	if (bIsOnAttackMode)
	{
		const FRotator DeltaRotator = Character->GetBaseAimRotation() - Character->GetActorRotation();
		Pitch = DeltaRotator.Pitch;
	}
}