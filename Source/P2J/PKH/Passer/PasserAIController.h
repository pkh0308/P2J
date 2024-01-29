// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PasserAIController.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APasserAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	APasserAIController();

	void RunAI();
	void StopAI();

protected:
	virtual void OnPossess(APawn* InPawn) override;

	UPROPERTY()
	TObjectPtr<class UBlackboardData> BBData;

	UPROPERTY()
	TObjectPtr<class UBehaviorTree> BTData;

	float ChaseRangeDistance = 750.0f;
};
