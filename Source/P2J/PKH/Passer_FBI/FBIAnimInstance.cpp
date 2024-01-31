// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/FBIAnimInstance.h"
#include "PKH/Passer_FBI/Passer_FBI.h"
#include "GameFramework/CharacterMovementComponent.h"

UFBIAnimInstance::UFBIAnimInstance()
{
	MoveThreshold = 3.0f;
	RunThreshold = 300.0f;
}

void UFBIAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	OwningFBI = Cast<APasser_FBI>(GetOwningActor());
	if (OwningFBI)
	{
		FBIMovement = OwningFBI->GetCharacterMovement();
	}
}

void UFBIAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	if (nullptr == FBIMovement)
	{
		return;
	}

	MoveVelocity = FBIMovement->Velocity;
	bIsIdle = MoveVelocity.Size2D() < MoveThreshold;
	bIsRunning = MoveVelocity.Size2D() > RunThreshold;
	bIsDead = OwningFBI->GetIsDead();
	bIsRage = OwningFBI->GetIsRage();
}
