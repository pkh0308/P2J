// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PasserAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UPasserAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPasserAnimInstance();

protected:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TObjectPtr<class APasserBase> OwningPasser;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	TObjectPtr<class UCharacterMovementComponent> PasserMovement;
	
// Variables
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float MoveThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float RunThreshold;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = Player)
	FVector MoveVelocity;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsIdle : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsRunning : 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	uint8 bIsDead : 1;
};
