// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "../BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
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

	// �� �޽ø� �߰��ϰ� �ʹ�
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* gunMeshComp;

	/*UPROPERTY(EditAnywhere, Category = "Combat System", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<class HandGun> Sword;*/

	// �Ѿ˰����� ����� �ʹ�.
	// �Ѿ��� ���� FirePosition���Ͽ� ��ġ�ϰ�ʹ�

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ABulletActor> bulletFactory;

	UFUNCTION(BlueprintCallable)
	void OnActionFire();

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	
	UFUNCTION()
	void OnDamaged(int damage);
	void OnDead();

	UPROPERTY(EditAnywhere)
	int HP = 20;

	UPROPERTY(EditAnywhere)
	bool isDead = false;

	UFUNCTION(BlueprintCallable)
	void Attack();

	// �Ҹ� Ŭ����

};
