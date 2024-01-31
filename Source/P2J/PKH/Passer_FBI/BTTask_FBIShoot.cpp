// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/BTTask_FBIShoot.h"
#include "PKH/Passer_FBI/PasserFBIAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "PKH/Passer_FBI/Passer_FBI.h"
#include "PKH/Passer/PasserAIKey.h"

UBTTask_FBIShoot::UBTTask_FBIShoot()
{
}

EBTNodeResult::Type UBTTask_FBIShoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APasser_FBI* OwnerFBI = Cast<APasser_FBI>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == OwnerFBI)
	{
		return EBTNodeResult::Failed;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BBComp)
	{
		return EBTNodeResult::Failed;
	}

	OwnerFBI->Shoot();

	return EBTNodeResult::Succeeded;
}
