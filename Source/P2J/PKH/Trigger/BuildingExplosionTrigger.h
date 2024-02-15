// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Trigger/SequenceTrigger.h"
#include "BuildingExplosionTrigger.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API ABuildingExplosionTrigger : public ASequenceTrigger
{
	GENERATED_BODY()
	
protected:
	virtual void OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult ) override;

	// Particles
	UPROPERTY(EditAnywhere)
	TObjectPtr<class UParticleSystem> VFX_Explosion;

	UPROPERTY( EditAnywhere )
	TObjectPtr<class UParticleSystem> VFX_Fire;

	// Sound
	UPROPERTY( EditAnywhere )
	TObjectPtr<class USoundBase> SFX_Explosion_1;

	UPROPERTY( EditAnywhere )
	TObjectPtr<class USoundBase> SFX_Explosion_2;

	// Camera Shake
	UPROPERTY( EditAnywhere )
	TSubclassOf<class UCameraShakeBase> BuildingShakeClass;

	float InnerRadius = 30000.0f;
	float OuterRadius = 50000.0f;
};
