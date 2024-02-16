// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../AIFSM.h"
#include "EnemyAI.generated.h"

UCLASS()
class P2J_API AEnemyAI : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemyAI();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// 총 메시를 추가하고 싶다
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* gunMeshComp;

	/*UPROPERTY(EditAnywhere, Category = "Combat System", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class HandGun> Sword;*/

	// 총알공장을 만들고 싶다.
	// 총알을 만들어서 FirePosition소켓에 배치하고싶다

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UArrowComponent* firePosition;

	UFUNCTION(BlueprintCallable)
	void OnActionFire();
	
	// AutoFire 타이머
	FTimerHandle fireTimerHandle;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	

	UFUNCTION()
	void OnDamaged(int damage);
	void OnDead();

	UPROPERTY(EditAnywhere)
	int32 maxHP = 3;

	UPROPERTY( EditAnywhere )
	int32 hp = maxHP;

	UPROPERTY(EditAnywhere)
	bool isDead = false;

	UFUNCTION(BlueprintCallable)
	void Attack();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class UAIFSM* aiFSM;

};
