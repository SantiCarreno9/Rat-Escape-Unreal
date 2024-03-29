// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class AProjectile;
class AWeapon;

UCLASS()
class CPP_GROUP_PROJECT_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

	//------------VARIABLES-----------------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	FName HeadBoneName = TEXT("Head");

	//------------PROPERTIES-----------------
	// Projectile class to spawn.

	// FPS camera.
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> CameraComponent;	

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<UChildActorComponent> WeaponActor;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<AWeapon> Weapon;	

	
public:
	// Sets default values for this character's properties
	ACustomCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:

	//------------METHODS-----------------	

	// Move on both directions
	UFUNCTION()
	void Move(FVector2D Value);

	// Rotates the camera
	UFUNCTION(BlueprintNativeEvent)
	void Look(FVector2D Value);

	// Function that handles firing projectiles.
	UFUNCTION()
	void Fire();

};
