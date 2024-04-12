// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "CustomGameModeBase.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnPlayerDiedSignature, ACharacter*, Character);
/**
 *
 */
UCLASS()
class CPP_GROUP_PROJECT_API ACustomGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float RespawnTime = 2.0f;

public:
	const FOnPlayerDiedSignature& GetOnPlayerDied() const { return OnPlayerDied; }

	//Tries to Spawn the player's pawn.
	virtual void RestartPlayer(AController* NewPlayer) override;

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void Respawn(AController* ControllerRef);
	//Called when Player character has died.
	UFUNCTION()
	virtual void PlayerDied(ACharacter* Character);

	//Signature to bind delegate. 
	UPROPERTY()
	FOnPlayerDiedSignature OnPlayerDied;
};
