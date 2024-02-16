// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/BTTask_FBIAttack.h"
#include "PKH/Passer_FBI/PasserFBIAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "PKH/Passer/PasserBase.h"
#include "PKH/Passer/PasserAIKey.h"

UBTTask_FBIAttack::UBTTask_FBIAttack()
{

}

EBTNodeResult::Type UBTTask_FBIAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	OwnerPasser->SetActorRotation( DirectionVec.GetSafeNormal().ToOrientationRotator() );
	OwnerPasser->BeginAttack();
	OwnerPasser->SetEndAttackDelegate(OnAttakFinished);

	return EBTNodeResult::InProgress;
}
