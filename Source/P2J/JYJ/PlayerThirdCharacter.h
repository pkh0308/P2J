// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PlayerThirdCharacter.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APlayerThirdCharacter : public APlayerZeroCharacter
{
	GENERATED_BODY()

public:
	APlayerThirdCharacter();

	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void Tick(float DeltaTime) override;

	void Zoom();
	void ZoomIn();
	void ZoomOut();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	float targetFOV = 90;

};
