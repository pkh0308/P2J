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

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* SMGMeshComp;	//SMG11Y

	UPROPERTY(EditAnywhere)
	class UParticleSystem* expVFX;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class AWeaponActor> Gun;

	UFUNCTION()
	void AttachWeapon(TSubclassOf<AWeaponActor> Weapon) const;

	

};
