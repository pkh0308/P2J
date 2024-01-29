// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/PasserAIController.h"
#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Passer/PasserAIKey.h"

APasserAIController::APasserAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/PKH/AI/BB_Passer.BB_Passer'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/PKH/AI/BT_Passer.BT_Passer'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}

void APasserAIController::RunAI()
{
	UBlackboardComponent* BlackBoardComp = Blackboard;
	if (UseBlackboard(BBData, BlackBoardComp))
	{
		bool RunResult = RunBehaviorTree(BTData);

		BlackBoardComp->SetValueAsBool(PASSER_KEY_ISHITDELAY, false);
		BlackBoardComp->SetValueAsFloat(PASSER_KEY_CHASERANGE, ChaseRangeDistance);
		BlackBoardComp->SetValueAsVector(PASSER_KEY_HOMELOCATION, BlackBoardComp->GetOwner()->GetActorLocation());
	}
}

void APasserAIController::StopAI()
{
	UBehaviorTreeComponent* BTComp = Cast<UBehaviorTreeComponent>(BrainComponent);
	if (BTComp)
	{
		BTComp->StopTree();
	}
}

void APasserAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	RunAI();
}
