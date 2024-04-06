// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "CustomCharacter.generated.h"

class UCameraComponent;
class USkeletalMeshComponent;
class USpringArmComponent;
class AProjectile;
class AWeapon;
class ACharacterHUD;

UCLASS()
class CPP_GROUP_PROJECT_API ACustomCharacter : public ACharacter
{
	GENERATED_BODY()

	//------------VARIABLES-----------------
	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	FName HeadBoneName = TEXT("Head");

	UPROPERTY(EditAnywhere, meta = (AllowPrivateAccess = true))
	float CameraTransitionTime = 1.0f;

	bool bIsOnThirdPersonView = true;

	bool bIsOnAttackMode = false;

	//------------PROPERTIES-----------------
	// Projectile class to spawn.

	// FPS camera.
	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UCameraComponent> FPSCameraComponent;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<UChildActorComponent> WeaponActor;

	UPROPERTY(EditAnywhere, Category = Weapon)
	TObjectPtr<AWeapon> Weapon;

	// Third person
	/** Third person camera */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<UCameraComponent> TPCameraComponent;

	/** Camera boom positioning the camera above the character */
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera, meta = (AllowPrivateAccess = "true"))
	TObjectPtr<USpringArmComponent> TPCameraBoom;

	UPROPERTY(EditDefaultsOnly, meta = (AllowPrivateAccess = true))
	TObjectPtr<UStaticMeshComponent> BackWeapon;

	TObjectPtr<APlayerController> PlayerController;	

	TObjectPtr<ACharacterHUD> CharacterHUD;

	void PlayCameraTransition(AActor* TargetCamera);


public:
	// Sets default values for this character's properties
	ACustomCharacter();

	virtual void Falling() override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	//Called when our Actor is destroyed during Gameplay.
	virtual void Destroyed();

public:

	//------------METHODS-----------------	

	FORCEINLINE bool GetIsOnAttackMode() { return bIsOnAttackMode; }

	// Move on both directions
	UFUNCTION()
	void Move(FVector2D Value);

	// Rotates the camera
	UFUNCTION(BlueprintNativeEvent)
	void Look(FVector2D Value);

	// Function that handles firing projectiles.
	UFUNCTION()
	void Fire();		

	void SwitchToFirstPersonPerspective();
	
	void SwitchToThirdPersonPerspective();

	void SwitchCamera();

	void SwitchMode();

	void SwitchToAttackMode();

	void SwitchToNormalMode();

	void SetControllerRef(APlayerController* PController);
};
