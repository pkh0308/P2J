// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/PasserBase.h"
#include "PKH/Passer/PasserAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Passer/PasserAIKey.h"
#include "JYJ/PlayerZeroCharacter.h"

// Sets default values
APasserBase::APasserBase()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = APasserAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Collision
	GetMesh()->SetCollisionProfileName(TEXT("Enemy"));

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimRef(TEXT("/Game/PKH/Animations/PasserA/ABP_PasserA.ABP_PasserA_C"));
	if (AnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserA/AM_PasserAttack.AM_PasserAttack'"));
	if (AttackMontageRef.Object)
	{
		AttackMontage = AttackMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DamagedMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserA/AM_PasserDamaged.AM_PasserDamaged'"));
	if (DamagedMontageRef.Object)
	{
		DamagedMontage = DamagedMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserA/AM_PasserDeath.AM_PasserDeath'"));
	if (DeathMontageRef.Object)
	{
		DeathMontage = DeathMontageRef.Object;
	}

	// Status
	Hp = 5;
	WalkSpeed = 150;
	RunSpeed = 350;
}

void APasserBase::BeginPlay()
{
	Super::BeginPlay();
	
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
	PasserAnimInstance = GetMesh()->GetAnimInstance();
}

void APasserBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APasserBase::OnDamaged(int32 InDamage, AActor* NewTarget)
{
	if (IsDamagedDelay || IsDead)
	{
		return;
	}
	IsDamagedDelay = true;

	Hp -= InDamage;
	if (Hp <= 0)
	{
		OnDie();
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		PlayMontage(DamagedMontage);

		UBlackboardComponent* BBComp = GetBlackboard();
		if (BBComp)
		{
			BBComp->SetValueAsBool(PASSER_KEY_ISHITDELAY, true);
			BBComp->SetValueAsObject(PASSER_KEY_TARGET, NewTarget);
		}
	}
}

void APasserBase::OnDamagedEnd()
{
	OnDamagedFinished.ExecuteIfBound();
	IsDamagedDelay = false;

	UBlackboardComponent* BBComp = GetBlackboard();
	if (BBComp)
	{
		BBComp->SetValueAsBool(PASSER_KEY_ISHITDELAY, false);
	}
}

void APasserBase::OnDie()
{
	GetMesh()->GetAnimInstance()->Montage_Play(DeathMontage);
	GetBlackboard()->SetValueAsObject(PASSER_KEY_TARGET, nullptr);
	IsDead = true;
	GetController()->UnPossess();
}

void APasserBase::BeginAttack()
{
	PlayMontage(AttackMontage);
}

void APasserBase::AttackHit()
{
	TArray<FOverlapResult> OverlapResults;
	const FVector AttackCenterVec = GetActorLocation() + GetActorForwardVector() * 80;
	FCollisionObjectQueryParams Param;

	bool OverlapRes = GetWorld()->OverlapMultiByObjectType(OverlapResults, AttackCenterVec, FQuat::Identity, Param, FCollisionShape::MakeSphere(AttackRadius));
	if (OverlapRes)
	{
		for (int i = 0; i < OverlapResults.Num(); i++)
		{
			APlayerZeroCharacter* PlayerCharacter = Cast<APlayerZeroCharacter>(OverlapResults[i].GetActor());
			if (PlayerCharacter)
			{
				PlayerCharacter->TakePlayerDamaged(1);
				break;
			}
		}
	}
}

void APasserBase::EndAttack()
{
	OnAttackFinished.ExecuteIfBound();
}

void APasserBase::SetSpeedToWalk()
{
	GetCharacterMovement()->MaxWalkSpeed = WalkSpeed;
}

void APasserBase::SetSpeedToRun()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
}

class UBlackboardComponent* APasserBase::GetBlackboard() const
{
	APasserAIController* PasserController = Cast< APasserAIController>(GetController());
	if (PasserController)
	{
		return PasserController->GetBlackboardComponent();
	}

	return nullptr;
}

#pragma region Animation
void APasserBase::PlayMontage(UAnimMontage* NewMontage, float InPlayRate)
{
	if (PasserAnimInstance)
	{
		PasserAnimInstance->StopAllMontages(0.0f);
		PasserAnimInstance->Montage_Play(NewMontage, InPlayRate);
	}
}
#pragma endregion

void APasserBase::SetEndAttackDelegate(FOnPasserAttackFinished NewOnAttackFinished)
{
	OnAttackFinished = NewOnAttackFinished;
}

void APasserBase::SetEndDamagedDelegate(FOnPasserDamagedFinished NewOnDamagedFinished)
{
	OnDamagedFinished = NewOnDamagedFinished;
}
