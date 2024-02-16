// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIFSM.generated.h"

UENUM(BlueprintType)
enum class EAIState : uint8
{ 
	IDLE   ,
	MOVE   ,
	ATTACK ,
	DAMAGE ,
	DIE    ,
};

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class P2J_API UAIFSM : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UAIFSM();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAIState state;

	UPROPERTY(EditAnywhere)
	float attackDist = 450;

	UPROPERTY(EditAnywhere)
	class AActor* target;

	UPROPERTY(EditAnywhere)
	class AEnemyAI* me;

	void TickIdle();
	void TickMove();
	void TickAttack();
	void TickDamage();
	void TickDie();

	void DoDamageEnd();

public:
	bool isDieDone;

	float currentTime;

	float attackWaitTime = 1;

	void TakeDamage( int damage );

	void SetState(EAIState next);

	// 공격 대기 시간
	UPROPERTY(EditAnywhere)
	float attackDelayTime = 2.0f;

	UPROPERTY(EditDefaultsOnly)
	class UAnimMontage* enemyMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool attackState;


	bool bAutoFire;
	float currentTimeAutoFire;
	float autoFireTime = 2;


};
