// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/BTDecorator_FBIRun.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PKH/Passer/PasserAIKey.h"
#include "Passer_FBI.h"

UBTDecorator_FBIRun::UBTDecorator_FBIRun()
{
	NodeName = TEXT("Run");
}

bool UBTDecorator_FBIRun::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
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

	APasser_FBI* FBI = Cast<APasser_FBI>(OwnerPawn);
	if (FBI)
	{
		return FBI->GetIsDead();
	}

	return SuperResult;
}
