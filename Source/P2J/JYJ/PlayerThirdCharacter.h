// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PlayerThirdCharacter.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APlayerThirdCharacter : public APlayerZeroCharacter
{
	GENERATED_BODY()

public:
	APlayerThirdCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void Zoom();
	void ZoomIn();
	void ZoomOut();
	void OnActionChooseSMG11();
	void OnActionFire();

	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetFOV = 90;

	UPROPERTY(EditAnywhere)
	class UParticleSystem* expVFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeaponActor> Gun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpotLightComponent* lightCookie;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USpotLightComponent* playerLight;

	UFUNCTION()
	void AttachWeapon(TSubclassOf<AWeaponActor> Weapon);
	
	UPROPERTY(EditAnywhere)
	bool bValidRifle;

	UPROPERTY(EditAnywhere)
	bool bAttack;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOnZoomRifle;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class UUserWidget> crossHairFactory;

	UPROPERTY()
	class UUserWidget* crossHairUI;

	UPROPERTY(EditDefaultsOnly)
	class AWeaponActor* Rifle;

	UPROPERTY(EditAnywhere)
	class USoundBase* fireSound;

	void OnActionCrouchStart();
	void OnActionCrouchEnd();

	virtual void gameOverText() override;

	virtual void TakePlayerDamaged( int damage ) override;


};
