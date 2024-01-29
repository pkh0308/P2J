// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_PasserAttack.generated.h"

DECLARE_DELEGATE(FOnPasserAttackFinished);
DECLARE_DELEGATE(FOnPasserDamagedFinished);

/**
 * 
 */
UCLASS()
class P2J_API UBTTask_PasserAttack : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_PasserAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
