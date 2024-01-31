// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Pkh/Passer/BTTask_PasserAttack.h"
#include "PasserBase.generated.h"

UCLASS()
class P2J_API APasserBase : public ACharacter
{
	GENERATED_BODY()

public:
	APasserBase();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

protected:
	int32 Hp;
	float WalkSpeed;
	float RunSpeed;
	bool IsDead = false;

	float AttackRadius = 50.0f;

public:
	UFUNCTION(BlueprintCallable)
	virtual void OnDamaged(int32 InDamage, AActor* NewTarget);

	virtual void OnDamagedEnd();

	virtual void OnDie();

	void BeginAttack();

	void AttackHit();

	void EndAttack();

	// Speed
	void SetSpeedToWalk();
	void SetSpeedToRun();

protected:
	class UBlackboardComponent* GetBlackboard() const;

// Animation
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimInstance> PasserAnimInstance;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> AttackMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> DamagedMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UAnimMontage> DeathMontage;

	void PlayMontage(UAnimMontage* NewMontage, float InPlayRate = 1.0f);

	FOnPasserAttackFinished OnAttackFinished;
	FOnPasserDamagedFinished OnDamagedFinished;

public:
	FORCEINLINE	bool GetIsDead() const { return IsDead;  }

	void SetEndAttackDelegate(FOnPasserAttackFinished NewOnAttackFinished);
	void SetEndDamagedDelegate(FOnPasserDamagedFinished NewOnDamagedFinished);
};
