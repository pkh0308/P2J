// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PKHGameMode.generated.h"

UENUM()
enum class EQuestType : uint8
{
	Q1_FightWithMan = 0,
	Q2_GetIDCard,
	Q3_EnterBuilding,
	Q4_PlantBombs,
	Q5_ExitBuilding,
	Q6_EnterAsAFireman,
	Q7_GetTheDisk,
	Q8_EscapeBuilding,
	Q9_ToTheHome,
	AllClear
};

/**
 * 
 */
UCLASS()
class P2J_API APKHGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	APKHGameMode();

protected:
	virtual void BeginPlay() override;

// Quest
protected:
	EQuestType CurQuest;

public:
	FORCEINLINE bool CheckCurQuest(enum EQuestType Type) { return CurQuest == Type; }

	void ClearCurQuest();
};
