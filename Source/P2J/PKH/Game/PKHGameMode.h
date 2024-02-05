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

// Level
protected:
	FString LevelName_1 = TEXT("Demo_Copy");
	FString LevelName_2 = TEXT("Level2");
	FString LevelName_3 = TEXT("Level3");

	int32 LevelIdx = 0;

// Quest
protected:
	EQuestType CurQuest;

public:
	FORCEINLINE bool CheckCurQuest(enum EQuestType Type) { return CurQuest == Type; }

	void ClearCurQuest();

// Time & Kill Count
protected:
	int32 Seconds = 0;
	int32 KillCount = 0;

public:
	FORCEINLINE void KillCountUp() { KillCount++; }

// UI
protected:
	// Guide
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UQuestGuideWidget> QuestGuideUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UQuestGuideWidget> QuestGuideUI;

	// Fade Out
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UUserWidget> FadeOutUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UUserWidget> FadeOutUI;

	// Oxygen
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UOxygenWidget> OxygenUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UOxygenWidget> OxygenUI;

	// Game Clear
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UQuestClearWidget> GameClearUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UQuestClearWidget> GameClearUI;

	// GameOver
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TSubclassOf<class UGameOverWidget> GameOverUIClass;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UGameOverWidget> GameOverUI;

public:
	void SetQuestGuideText(FString GuideString, float DisplayTime = 5.0f);

	void ShowFadeOut();

	void StartOxygenTimer();

	void GameClear();

	void GameOver(FString NewFailReasonString);
};
