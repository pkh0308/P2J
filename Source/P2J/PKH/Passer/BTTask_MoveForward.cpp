// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/BTTask_MoveForward.h"
#include "PKH/Passer/PasserAIController.h"
#include "NavigationSystem.h"
#include "BehaviorTree/BlackBoardComponent.h"

UBTTask_MoveForward::UBTTask_MoveForward()
{

}

EBTNodeResult::Type UBTTask_MoveForward::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
		FVector TargetLocation = IsForward ? OwnerPawn->GetActorForwardVector() * LocationOffset : OwnerPawn->GetActorForwardVector() * LocationOffset * -1;
		BBComp->SetValueAsVector(TEXT("MoveLocation"), TargetLocation);
		IsForward = !IsForward;
		return EBTNodeResult::Succeeded;
	}

	return Result;
}
