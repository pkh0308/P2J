// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerAnimInstance.h"
#include "PlayerZeroCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.0f;

	//몽타주 변수 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM(TEXT("/Script/Engine.AnimMontage'/Game/JYJ/Animations/AM_Player.AM_Player'"));
	if (AM.Succeeded())
	{
		AttackMontage = AM.Object;
	}


}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	/*
	PlayerZeroCharacter = Cast<APlayerZeroCharacter>(TryGetPawnOwner());
	if (PlayerZeroCharacter) {
		//#include "GameFramework/CharacterMovementComponent.h" 필요.
		PlayerZeroMovement = PlayerZeroCharacter->GetCharacterMovement();
	}
	*/


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
	//Direction = CalculateDirection(playerZero->GetVelocity(), playerZero->GetActorRotation());



}

void UPlayerAnimInstance::PlayerAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}

}

/*
void UPlayerAnimInstance::PlayerWalk()
{
	
	if (!Montage_IsPlaying(walkMontage))
	{
		Montage_Play(walkMontage, 1.f);
	}
	

	auto Player = TryGetPawnOwner();
	if (::IsValid(Player))
	{
		CurrentPlayerSpeed = Player->GetVelocity().Size();
		auto Character = Cast<ACharacter>(Player);

	}

	if (CurrentPlayerSpeed > 0) {
		isWalking = true;
	}
	else 
	{
		isWalking = false;
	}

	


}
*/
