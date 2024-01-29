// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetMoveLocation.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTTask_SetMoveLocation : public UBTTaskNode
{
	GENERATED_BODY()

public:
	UBTTask_SetMoveLocation();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

protected:
	bool IsForward = true;
	float LocationOffset = 1000;
	
};
