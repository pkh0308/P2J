// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Passer/PasserBase.h"
#include "Passer_FBI.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APasser_FBI : public APasserBase
{
	GENERATED_BODY()

public:
	APasser_FBI();

protected:
	virtual void BeginPlay() override;

	UPROPERTY()
	TObjectPtr<class UBlackboardComponent> BBComp;

public:
	virtual void Tick(float DeltaTime) override;

	virtual void OnDamaged(int32 InDamage, AActor* NewTarget) override;
	
	virtual void OnDie() override;

	virtual void OnDamagedEnd() override;

// Weapon
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> WeaponMeshComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ULevelSequencePlayer> SequencePlayer;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ULevelSequence> Sequence_FBIOut;

// Rage & Run
protected:
	bool IsRage = false;
	bool IsDropped = false;

	float FastRunSpeed = 500.0f;
	float RunDistance = 10000;

public:
	FORCEINLINE bool GetIsRage() const { return IsRage; }

// Shoot
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 ShootPower = 10;

	float ShootYOffset = 60.0f;
	float ShootZOffset = 80.0f;

	FVector PistolOffset = FVector(0, 0, 30);

public:
	void Shoot();

// Item
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class AItem_IDCard> IDCardFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class AItem_IDCard> IDCard;
};
