// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerAnimInstance.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.0f;
	isInAir = false;

	//��Ÿ�� ���� ��������
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM(TEXT("/Script/Engine.AnimMontage'/Game/JYJ/Animations/AM_Player.AM_Player'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}


}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

}

void UPlayerAnimInstance::NativeBeginPlay()
{
	Super::NativeBeginPlay();

	/*
	auto Player = TryGetPawnOwner();
	if (::IsValid(Player))
	{
		CurrentPlayerSpeed = Player->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Player);

	}
	*/

}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	auto playerZero = TryGetPawnOwner();
	if (!::IsValid(playerZero)) return;

	Speed = playerZero->GetVelocity().Size();
	auto Character = Cast<ACharacter>(playerZero);
	 
	if (Character)
	{
		isInAir = Character->GetMovementComponent()->IsFalling();
	}

}

void UPlayerAnimInstance::PlayerAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}

}

