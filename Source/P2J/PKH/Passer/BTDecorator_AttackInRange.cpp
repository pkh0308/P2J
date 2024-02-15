// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/BTDecorator_AttackInRange.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PKH/Passer/PasserAIKey.h"
#include "PKH/Passer_FBI/Passer_FBI.h"

UBTDecorator_AttackInRange::UBTDecorator_AttackInRange()
{
	NodeName = TEXT("CanAttack");
}

bool UBTDecorator_AttackInRange::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	bool SuperResult = Super::CalculateRawConditionValue(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == OwnerPawn)
	{
		return false;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BBComp)
	{
		return false;
	}

	APasser_FBI* FBI = Cast<APasser_FBI>( OwnerPawn );
	if (FBI)
	{
		if (FBI->GetIsRage())
		{
			return true;
		}
	}

	APawn* TargetActor = Cast<APawn>(BBComp->GetValueAsObject(PASSER_KEY_TARGET));
	if (TargetActor)
	{
		float DistanceToTarget = FVector::Distance(OwnerPawn->GetActorLocation(), TargetActor->GetActorLocation());
		return DistanceToTarget < AttackDistance;
	}

	return SuperResult;
}
