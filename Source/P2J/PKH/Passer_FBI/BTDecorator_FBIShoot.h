// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_FBIShoot.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTDecorator_FBIShoot : public UBTDecorator
{
	GENERATED_BODY()
	
public:
	UBTDecorator_FBIShoot();

protected:
	virtual bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

	float AttackDistance = 700.0f;
};
