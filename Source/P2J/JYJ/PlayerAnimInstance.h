// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
	UPlayerAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeBeginPlay() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(BlueprintReadOnly)
	class APlayerZeroCharacter* PlayerZeroCharacter;

	UPROPERTY(BlueprintReadOnly, Category = Movement)
	class UCharacterMovementComponent* PlayerZeroMovement;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Speed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool isInAir ;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float Direction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bIDLEJump;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bRifleValid;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bShootGun;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bOnZoomRifle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool bCrouch;

	UPROPERTY(BlueprintReadOnly)
	class APlayerThirdCharacter* PlayerThirdCharacter;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* PlayerMontage;

	/*
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* CleanMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage* RifleIdleMontage;
	*/

	void PlayerAttackMontage();
	void PlayerCleanMontage();
	void PlayerRifleFireMontage();
	void PlayerDeathMontage();
	void PlayerHitMontage();
	//void PlayerCrouch();


};
