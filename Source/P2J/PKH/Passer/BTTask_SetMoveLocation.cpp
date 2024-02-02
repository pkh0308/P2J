// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/BTTask_SetMoveLocation.h"
#include "PKH/Passer/PasserAIController.h"
#include "BehaviorTree/BlackBoardComponent.h"
#include "PKH/Passer/PasserAIKey.h"

UBTTask_SetMoveLocation::UBTTask_SetMoveLocation()
{

}

EBTNodeResult::Type UBTTask_SetMoveLocation::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	EBTNodeResult::Type Result = Super::ExecuteTask(OwnerComp, NodeMemory);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == OwnerPawn)
	{
		return EBTNodeResult::Failed;
	}
	
	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (BBComp)
	{
		FVector TargetDirection = OwnerPawn->GetActorForwardVector();
		TargetDirection.Z = 0;
		FVector TargetLocation = OwnerPawn->GetActorLocation();
		TargetLocation += IsForward ? TargetDirection * LocationOffset : TargetDirection * LocationOffset * -1;
		BBComp->SetValueAsVector(PASSER_KEY_MOVELOCATION, TargetLocation);
		IsForward = !IsForward;
		return EBTNodeResult::Succeeded;
	}

	return Result;
}
