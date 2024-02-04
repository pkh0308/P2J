// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/PKHGameMode.h"
#include "PKH/UI/QuestGuideWidget.h"
#include "Kismet/GameplayStatics.h"

APKHGameMode::APKHGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter> PawnRef(TEXT("/Game/PKH/Blueprints/BP_TestPlayer.BP_TestPlayer_C"));
	if (PawnRef.Class)
	{
		DefaultPawnClass = PawnRef.Class;
	}

	// UI
	static ConstructorHelpers::FClassFinder<UQuestGuideWidget> QuestGuideRef(TEXT("/Game/PKH/UI/WBP_QuestGuide.WBP_QuestGuide_C"));
	if (QuestGuideRef.Class)
	{
		QuestGuideUIClass = QuestGuideRef.Class;
	}
}

void APKHGameMode::BeginPlay()
{
	FString CurLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (CurLevelName == LevelName_1)
	{
		LevelIdx = 1;
		CurQuest = EQuestType::Q1_FightWithMan; 
	}
	else if(CurLevelName == LevelName_2)
	{
		LevelIdx = 2;
		CurQuest = EQuestType::Q4_PlantBombs;
	}
	else if (CurLevelName == LevelName_3)
	{
		LevelIdx = 3;
		CurQuest = EQuestType::Q7_GetTheDisk;
	}
	
	// UI
	QuestGuideUI = CreateWidget<UQuestGuideWidget>(GetWorld(), QuestGuideUIClass);
	if (QuestGuideUI)
	{
		QuestGuideUI->AddToViewport();

		switch (LevelIdx)
		{
		case 1:
			QuestGuideUI->SetQuestGuideText(TEXT("전화중인 남자에게 시비를 거십시오."));
			break;
		case 2:
			QuestGuideUI->SetQuestGuideText(TEXT("폭탄을 설치하십시오."));
			break;
		case 3:
			QuestGuideUI->SetQuestGuideText(TEXT("보안 디스크를 획득하십시오."));
			break;
		}
		
	}
}

void APKHGameMode::SetQuestGuideText(FString GuideString, float DisplayTime)
{
	QuestGuideUI->SetQuestGuideText(GuideString, DisplayTime);
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
