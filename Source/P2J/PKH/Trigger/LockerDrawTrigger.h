// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Trigger/SequenceTrigger.h"
#include "LockerDrawTrigger.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API ALockerDrawTrigger : public ASequenceTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult ) override;

	void OnSequenceFinished() override;

	bool IsTriggered = false;
};
