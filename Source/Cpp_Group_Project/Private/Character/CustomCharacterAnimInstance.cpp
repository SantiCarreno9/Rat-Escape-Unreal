// Fill out your copyright notice in the Description page of Project Settings.


#include "Character/CustomCharacterAnimInstance.h"
#include "GameFramework/Character.h"

UCustomCharacterAnimInstance::UCustomCharacterAnimInstance()
{
	Pitch = 0;
}

void UCustomCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	Character = Cast<ACharacter>(GetOwningActor());
}

void UCustomCharacterAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	if (Character == nullptr)
		return;

	const FRotator DeltaRotator = Character->GetBaseAimRotation() - Character->GetActorRotation();
	Pitch = DeltaRotator.Pitch;
}
