// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CustomCharacterAnimInstance.generated.h"

class ACustomCharacter;
/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UCustomCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	TObjectPtr<ACustomCharacter> Character;	

protected:

	UPROPERTY(BlueprintReadOnly)
	float Pitch;

	UPROPERTY(BlueprintReadOnly)
	float Speed;

	UPROPERTY(BlueprintReadOnly)
	bool bIsOnAttackMode;

	UPROPERTY(BlueprintReadOnly)
	bool bIsFalling;

public:

	UCustomCharacterAnimInstance();

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
