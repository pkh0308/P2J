// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "DestructibleDoorInterface.generated.h"

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UDestructibleDoorInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class P2J_API IDestructibleDoorInterface
{
	GENERATED_BODY()

public:
	virtual void DestroyActor() = 0;
};
