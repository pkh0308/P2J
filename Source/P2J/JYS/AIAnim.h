// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "AIFSM.h"
#include "AIAnim.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UAIAnim : public UAnimInstance
{
	GENERATED_BODY()
	
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation( float DeltaSeconds ) override;

public:
	UPROPERTY()
	class UAIFSM* aiFSM;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	EAIState state;
	
	UFUNCTION()
	void AnimNotify_DieEnd();
	
};
