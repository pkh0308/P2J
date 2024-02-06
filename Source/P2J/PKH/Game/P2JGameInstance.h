// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "P2JGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UP2JGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
protected:
	int32 Seconds = 0;

public:
	FORCEINLINE	void AddSeconds(int32 InSeconds) { Seconds += InSeconds; }
	FORCEINLINE	int32 GetSeconds() const { return Seconds; }
};
