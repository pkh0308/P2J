// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/BTService_CalDistance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "PKH/Passer/PasserBase.h"
#include "PKH/Passer/PasserAIKey.h"

UBTService_CalDistance::UBTService_CalDistance()
{
	NodeName = TEXT("CalDistance");
	Interval = 1.0f;
}

void UBTService_CalDistance::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	APawn* OwnerPawn = Cast<APawn>(OwnerComp.GetAIOwner()->GetPawn());
	if (nullptr == OwnerPawn)
	{
		return;
	}

	UBlackboardComponent* BBComp = OwnerComp.GetBlackboardComponent();
	if (nullptr == BBComp)
	{
		return;
	}

	AActor* Target = Cast<AActor>(BBComp->GetValueAsObject(PASSER_KEY_TARGET));
	if (nullptr == Target)
	{
		return;
	}
	
	float BetweenDistance = FVector::Distance(OwnerPawn->GetActorLocation(), Target->GetActorLocation());
	if (BetweenDistance > BBComp->GetValueAsFloat(PASSER_KEY_CHASERANGE))
	{
		BBComp->SetValueAsObject(PASSER_KEY_TARGET, nullptr);
		Cast<APasserBase>(OwnerPawn)->SetSpeedToWalk();
	}
}
