// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/PasserFBIAIController.h"

APasserFBIAIController::APasserFBIAIController()
{
	static ConstructorHelpers::FObjectFinder<UBlackboardData> BBDataRef(TEXT("/Script/AIModule.BlackboardData'/Game/PKH/AI/BB_FBI.BB_FBI'"));
	if (BBDataRef.Object)
	{
		BBData = BBDataRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> BTDataRef(TEXT("/Script/AIModule.BehaviorTree'/Game/PKH/AI/BT_FBI.BT_FBI'"));
	if (BTDataRef.Object)
	{
		BTData = BTDataRef.Object;
	}
}
