// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
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

	UPROPERTY(EditAnywhere)
	class USpringArmComponent* springArmComp;

	UPROPERTY(EditAnywhere)
	class UCameraComponent*	p1camComp;

	UPROPERTY(EditAnywhere)
	FVector direction;

	void Move();

	void OnAxisVertical(float value);
	void OnAxisHorizontal(float value);

	void OnActionJump();

	void OnAxisTurnYaw(float value);			//Yaw
	void OnAxisLookupPitch(float value);		//Pitch

};
