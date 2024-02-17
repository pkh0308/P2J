// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotify.h"
#include "AnimNotify_CleanEnd.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UAnimNotify_CleanEnd : public UAnimNotify
{
	GENERATED_BODY()
	virtual void Notify( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation ) override;
	
};
