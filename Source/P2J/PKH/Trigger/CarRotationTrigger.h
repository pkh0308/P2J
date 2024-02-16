// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Trigger/SequenceTrigger.h"
#include "CarRotationTrigger.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API ACarRotationTrigger : public ASequenceTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult ) override;

};
