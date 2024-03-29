// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "CustomCharacterAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class CPP_GROUP_PROJECT_API UCustomCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

	TObjectPtr<ACharacter> Character;

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float Pitch;

public:

	UCustomCharacterAnimInstance();

	virtual void NativeInitializeAnimation();

	virtual void NativeUpdateAnimation(float DeltaSeconds) override;
};
