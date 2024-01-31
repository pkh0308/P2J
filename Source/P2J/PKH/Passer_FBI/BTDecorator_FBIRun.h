// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_FBIRun.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTDecorator_FBIRun : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_FBIRun();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
