// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_FBIShoot.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTTask_FBIShoot : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	UBTTask_FBIShoot();

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
};
