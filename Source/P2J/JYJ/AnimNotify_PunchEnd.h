// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_PunchEnd.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UAnimNotify_PunchEnd : public UAnimNotify
{
	GENERATED_BODY()

public:
	virtual void Notify( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation ) override;
	
};
