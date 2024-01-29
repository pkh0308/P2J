// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTService.h"
#include "BTService_CalDistance.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UBTService_CalDistance : public UBTService
{
	GENERATED_BODY()

public:
	UBTService_CalDistance();

protected:
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	
};
