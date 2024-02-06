// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/PKHGameMode.h"
#include "PKH/UI/QuestGuideWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/UI/OxygenWidget.h"
#include "PKH/UI/QuestClearWidget.h"
#include "PKH/UI/GameOverWidget.h"
#include "P2JGameInstance.h"

APKHGameMode::APKHGameMode()
{
	static ConstructorHelpers::FClassFinder<ACharacter> PawnRef(TEXT("/Game/JYJ/Blueprints/BP_PlayerZero.BP_PlayerZero_C"));
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

	static ConstructorHelpers::FClassFinder<UUserWidget> FadeOutUIRef(TEXT("/Game/PKH/UI/WBP_FadeOut.WBP_FadeOut_C"));
	if (FadeOutUIRef.Class)
	{
		FadeOutUIClass = FadeOutUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UOxygenWidget> OxygenUIRef(TEXT("/Game/PKH/UI/WBP_OxygenWidget.WBP_OxygenWidget_C"));
	if (OxygenUIRef.Class)
	{
		OxygenUIClass = OxygenUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UQuestClearWidget> GameClearUIRef(TEXT("/Game/PKH/UI/WBP_QuestClear.WBP_QuestClear_C"));
	if (GameClearUIRef.Class)
	{
		GameClearUIClass = GameClearUIRef.Class;
	}

	static ConstructorHelpers::FClassFinder<UGameOverWidget> GameOverUIRef(TEXT("/Game/PKH/UI/WBP_GameOver.WBP_GameOver_C"));
	if (GameOverUIRef.Class)
	{
		GameOverUIClass = GameOverUIRef.Class;
	}

	LevelNames.Add(TEXT("Demo_Copy"));
	LevelNames.Add(TEXT("Level2_Test"));
	LevelNames.Add(TEXT("Level3"));
}

void APKHGameMode::BeginPlay()
{
	FString CurLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (CurLevelName == LevelNames[0])
	{
		LevelIdx = 1;
		CurQuest = EQuestType::Q3_EnterBuilding; 
	}
	else if(CurLevelName == LevelNames[1])
	{
		LevelIdx = 2;
		CurQuest = EQuestType::Q4_PlantBombs;
	}
	else if (CurLevelName == LevelNames[2])
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
		default:
			QuestGuideUI->SetQuestGuideText(TEXT(""));
			break;
		}
	}

	FadeOutUI = CreateWidget<UUserWidget>(GetWorld(), FadeOutUIClass);
	if (FadeOutUI)
	{
		FadeOutUI->AddToViewport();
		FadeOutUI->SetVisibility(ESlateVisibility::Hidden);
	}

	OxygenUI = CreateWidget<UOxygenWidget>(GetWorld(), OxygenUIClass);
	if (OxygenUI)
	{
		OxygenUI->AddToViewport();
		OxygenUI->SetVisibility(ESlateVisibility::Hidden);
	}

	GameClearUI = CreateWidget<UQuestClearWidget>(GetWorld(), GameClearUIClass);
	if (GameClearUI)
	{
		GameClearUI->AddToViewport();
		GameClearUI->SetVisibility(ESlateVisibility::Hidden);
	}

	GameOverUI = CreateWidget<UGameOverWidget>(GetWorld(), GameOverUIClass);
	if (GameOverUI)
	{
		GameOverUI->AddToViewport();
		GameOverUI->SetVisibility(ESlateVisibility::Hidden);
	}

	// Timer
	GetWorldTimerManager().SetTimer(TimeHandle, FTimerDelegate::CreateLambda(
		[this]() {
			Seconds++;
		}), 1.0f, false);
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

void APKHGameMode::ShowFadeOut()
{
	FadeOutUI->SetVisibility(ESlateVisibility::Visible);
}

void APKHGameMode::StartOxygenTimer()
{
	OxygenUI->SetVisibility(ESlateVisibility::Visible);
	OxygenUI->StartOxygenTimer();
}

void APKHGameMode::StopOxygenTimer()
{
	OxygenUI->SetVisibility(ESlateVisibility::Hidden);
	OxygenUI->StopOxygenTimer();
}

void APKHGameMode::GameClear()
{
	// Update Seconds
	if (TimeHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TimeHandle);
	}
	UP2JGameInstance* GI = Cast<UP2JGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		Seconds += GI->GetSeconds();
	}

	GameClearUI->SetClearUIText(Seconds, OxygenUI->GetOxygenRate(), KillCount);
	GameClearUI->SetVisibility(ESlateVisibility::Visible);

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
		[&]() {
			GameClearUI->SetVisibility(ESlateVisibility::Hidden);
		}), 7.0f, false);
}

void APKHGameMode::GameOver(FString NewFailReasonString)
{
	// Hide UI
	QuestGuideUI->SetVisibility(ESlateVisibility::Hidden);
	OxygenUI->SetVisibility(ESlateVisibility::Hidden);

	// Game Over
	GameOverUI->SetFailReasonText(NewFailReasonString);
	GameOverUI->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void APKHGameMode::OpenLevel(enum ELevelSelect NewLevel)
{
	// Time Save
	if (TimeHandle.IsValid())
	{
		GetWorldTimerManager().ClearTimer(TimeHandle);
	}
	UP2JGameInstance* GI = Cast<UP2JGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->AddSeconds(Seconds);
	}

	uint8 Idx = (uint8)NewLevel;
	UGameplayStatics::OpenLevel(GetWorld(), LevelNames[Idx]);
}
