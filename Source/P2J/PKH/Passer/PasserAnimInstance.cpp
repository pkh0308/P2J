// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/PasserAnimInstance.h"
#include "PKH/Passer/PasserBase.h"
#include "GameFramework/CharacterMovementComponent.h"

UPasserAnimInstance::UPasserAnimInstance()
{
	MoveThreshold = 3.0f;
	RunThreshold = 300.0f;
}

void UPasserAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningPasser = Cast<APasserBase>(GetOwningActor());
	if (OwningPasser)
	{
		PasserMovement = OwningPasser->GetCharacterMovement();
	}
}

void UPasserAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (nullptr == PasserMovement)
	{
		return;
	}

	MoveVelocity = PasserMovement->Velocity;
	bIsIdle = MoveVelocity.Size2D() < MoveThreshold;
	bIsRunning = MoveVelocity.Size2D() > RunThreshold;
	bIsDead = OwningPasser->GetIsDead();
}
