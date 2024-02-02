// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/PKHGameMode.h"

APKHGameMode::APKHGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter> PawnRef(TEXT("/Game/PKH/Blueprints/BP_TestPlayer.BP_TestPlayer_C"));
	if (PawnRef.Class)
	{
		DefaultPawnClass = PawnRef.Class;
	}
}

void APKHGameMode::BeginPlay()
{
	CurQuest = EQuestType::Q1_FightWithMan;
}

void APKHGameMode::ClearCurQuest()
{
	if (CurQuest == EQuestType::AllClear)
	{
		return;
	}

	UE_LOG(LogTemp, Log, TEXT("Quest Clear: %s"), *UEnum::GetValueAsString(CurQuest));
	CurQuest = EQuestType((uint8)CurQuest + 1);
}
