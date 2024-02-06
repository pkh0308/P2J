// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Trigger/SequenceTrigger.h"
#include "ExplodeTrigger.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API AExplodeTrigger : public ASequenceTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	bool IsTriggered = false;

// VFX
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> VFX_Explosion;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FRotator ExplodeRotation;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FVector ExplodeScale = FVector(1.0f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float InnerRadius = 1500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float OuterRadius = 3000.0f;

// Camera Shake
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UCameraShakeBase> ExplodeShakeClass;
};
