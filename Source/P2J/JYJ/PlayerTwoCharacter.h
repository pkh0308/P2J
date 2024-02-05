// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PlayerTwoCharacter.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APlayerTwoCharacter : public APlayerZeroCharacter
{
	GENERATED_BODY()
	
public:
	APlayerTwoCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void cleanStart();
	void cleanEnd();

	void putUp();
	void putDown();

};
