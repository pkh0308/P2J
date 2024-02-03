// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerAnimInstance.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "PlayerThirdCharacter.h"
#include "PlayerTwoCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.0f;
	isInAir = false;
	bRifleValid = false;

	//몽타주 변수 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AM(TEXT("/Script/Engine.AnimMontage'/Game/JYJ/Animations/Player1/AM_Player1.AM_Player1'"));
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

	auto player = TryGetPawnOwner();
	if (!::IsValid(player)) return;

	auto Character = Cast<ACharacter>(player);
	if (Character)
	{
		isInAir = Character->GetMovementComponent()->IsFalling();
		Speed = player->GetVelocity().Size();
	}

	if (player == Cast<APlayerThirdCharacter>(Character)) {
		auto playerThree = Cast<APlayerThirdCharacter>(Character);
		bRifleValid = playerThree->bValidRifle;
		bShootGun = playerThree->bAttack;
	}
	else if (player == Cast<APlayerTwoCharacter>(Character))
	{
		auto playerTwo = Cast<APlayerTwoCharacter>(Character);
	}

	

}

void UPlayerAnimInstance::PlayerAttackMontage()
{
	if (!Montage_IsPlaying(AttackMontage))
	{
		Montage_Play(AttackMontage, 1.0f);
	}

}

void UPlayerAnimInstance::PlayerRifleIdleMontage()
{
	Montage_JumpToSection(FName("Rifle_IDLE"), AttackMontage);
	UE_LOG(LogTemp, Warning, TEXT("test1"));
}


