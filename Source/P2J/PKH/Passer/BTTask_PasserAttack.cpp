// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/BTTask_PasserAttack.h"
#include "PKH/Passer/PasserAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "PKH/Passer/PasserBase.h"
#include "PKH/Passer/PasserAIKey.h"
#include "Kismet/KismetMathLibrary.h"

UBTTask_PasserAttack::UBTTask_PasserAttack()
{
}

EBTNodeResult::Type UBTTask_PasserAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APasserBase* OwnerPasser = Cast<APasserBase>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == OwnerPasser)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BBComp)
	{
		return EBTNodeResult::Failed;
	}

	if (BBComp->GetValueAsBool(PASSER_KEY_ISHITDELAY))
	{
		FOnPasserDamagedFinished OnDamagedFinished;
		OnDamagedFinished.BindLambda(
			[&]() {
				FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			});

		OwnerPasser->SetEndDamagedDelegate(OnDamagedFinished);
		return EBTNodeResult::InProgress;
	}

	FOnPasserAttackFinished OnAttakFinished;
	OnAttakFinished.BindLambda(
		[&]() {
			FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		});

	// Rotate
	AActor* Target = Cast<AActor>( BBComp->GetValueAsObject( PASSER_KEY_TARGET ) );
	if (nullptr == Target)
	{
		return EBTNodeResult::Failed;
	}

	FVector DirectionVec = Target->GetActorLocation() - OwnerPasser->GetActorLocation();
	FRotator TargetRotation = UKismetMathLibrary::MakeRotFromX( DirectionVec.GetSafeNormal() );
	OwnerPasser->SetActorRotation( TargetRotation );
	OwnerPasser->BeginAttack();
	OwnerPasser->SetEndAttackDelegate(OnAttakFinished);

	return EBTNodeResult::InProgress;
}
