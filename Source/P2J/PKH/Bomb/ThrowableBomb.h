// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "ThrowableBomb.generated.h"

UCLASS()
class P2J_API AThrowableBomb : public AActor
{
	GENERATED_BODY()
	
public:	
	AThrowableBomb();

protected:
	virtual void BeginPlay() override;

// Component
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> MeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UProjectileMovementComponent> ProjectileComp;

	UFUNCTION()
	void OnBoxCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

// Throw & Explode
public:
	UFUNCTION(BlueprintCallable)
	void ThrowBomb(FVector Direction, float DelayTime = 2.0f);

protected:
	void Explode();

// VFX
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UParticleSystem> VFX_Explosion;
};
