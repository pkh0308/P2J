// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerAnimInstance.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/PawnMovementComponent.h"
#include "PlayerThirdCharacter.h"
#include "PlayerTwoCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	Speed = 0.0f;
	isInAir = false;
	bRifleValid = false;
	bIDLEJump = false;

	//몽타주 변수 가져오기
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AMPlayer1(TEXT("/Script/Engine.AnimMontage'/Game/JYJ/Animations/Player1/AM_Player1.AM_Player1'"));
	if (AMPlayer1.Succeeded())
	{
		PlayerMontage = AMPlayer1.Object;
	}

	/*
	static ConstructorHelpers::FObjectFinder<UAnimMontage>AMPlayer2(TEXT("/Script/Engine.AnimMontage'/Game/JYJ/Animations/Player1/AM_Player1.AM_Player2'"));
	if (AMPlayer2.Succeeded())
	{
		CleanMontage = AMPlayer2.Object;
	}
	*/

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

		if (Character->GetCharacterMovement()->GetMaxJumpHeight() > 500) {
			bIDLEJump = true;
		}

	}

	if (player == Cast<APlayerThirdCharacter>(Character)) {
		auto playerThree = Cast<APlayerThirdCharacter>(Character);
		bRifleValid = playerThree->bValidRifle;
		bShootGun = playerThree->bAttack;
		bOnZoomRifle = playerThree->bOnZoomRifle;
	}
	else if (player == Cast<APlayerTwoCharacter>(Character))
	{
		auto playerTwo = Cast<APlayerTwoCharacter>(Character);
	}
	else {
		
	}

	

}

void UPlayerAnimInstance::PlayerAttackMontage()
{
	if (!Montage_IsPlaying(PlayerMontage))
	{
		Cast<APlayerZeroCharacter>(TryGetPawnOwner())->PlayAnimMontage(PlayerMontage, 1, TEXT("Punching"));
		
	}

}

void UPlayerAnimInstance::PlayerCleanMontage()
{
	if (!Montage_IsPlaying(PlayerMontage))
	{
		Cast<APlayerZeroCharacter>(TryGetPawnOwner())->PlayAnimMontage(PlayerMontage, 1, TEXT("Clean"));
	}
}

void UPlayerAnimInstance::PlayerRifleFireMontage()
{
	if (!Montage_IsPlaying(PlayerMontage))
	{
		Cast<APlayerZeroCharacter>(TryGetPawnOwner())->PlayAnimMontage(PlayerMontage, 1, TEXT("Fire"));
	}
}

/*
void UPlayerAnimInstance::PlayerCrouch()
{
	if (!Montage_IsPlaying(PlayerMontage))
	{
		Cast<APlayerZeroCharacter>(TryGetPawnOwner())->PlayAnimMontage(PlayerMontage, 1, TEXT("Crouch"));
	}
}
*/

