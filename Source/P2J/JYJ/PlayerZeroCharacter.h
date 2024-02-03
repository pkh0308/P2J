// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AnimAAttackInterface.h"
#include "PlayerZeroCharacter.generated.h"

UCLASS()
class P2J_API APlayerZeroCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerZeroCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

//protected:

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent*	p1camComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USphereComponent* punchComp;

	UPROPERTY(EditAnywhere)
	class UPlayerAnimInstance* PlayerAnim;

	UPROPERTY(EditAnywhere)
	FVector direction;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float SprintSpeedMultiplier;

	UFUNCTION()
	void OnAxisVertical(float value);
	
	UFUNCTION()
	void OnAxisHorizontal(float value);
	
	UFUNCTION()
	void OnAxisTurnYaw(float value);			//Yaw
	
	UFUNCTION()
	void OnAxisLookupPitch(float value);		//Pitch

	void OnActionJump();
	void Attack();
	void Sprint();
	void StopSprinting();
	void OnPunchingMontageEnded(UAnimMontage* Montage, bool bInterrupred);



};
