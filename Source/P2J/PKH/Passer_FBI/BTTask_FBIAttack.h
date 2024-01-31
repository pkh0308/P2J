// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FBIAttack.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTTask_FBIAttack : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FBIAttack();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
