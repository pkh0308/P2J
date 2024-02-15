// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Game/PKHGameMode.h"
#include "PKH/UI/QuestGuideWidget.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/UI/OxygenWidget.h"
#include "PKH/UI/QuestClearWidget.h"
#include "PKH/UI/GameOverWidget.h"
#include "P2JGameInstance.h"
#include "JYJ/PlayerHPBar.h"
#include "Components/AudioComponent.h"

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

	static ConstructorHelpers::FClassFinder<UPlayerHPBar> PlayerHpUIRef( TEXT( "/Game/JYJ/UI/WBP_PlayerHP.WBP_PlayerHP_C" ) );
	if (PlayerHpUIRef.Class)
	{
		PlayerHpUIClass = PlayerHpUIRef.Class;
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

	// Sound
	static ConstructorHelpers::FObjectFinder<USoundBase> BGM_Level3Ref( TEXT( "/Script/Engine.SoundWave'/Game/PKH/Sound/Level3/BGM_Level3.BGM_Level3'" ) );
	if (BGM_Level3Ref.Object)
	{
		BGM_Level3 = BGM_Level3Ref.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SFX_FireAlarmRef( TEXT( "/Script/Engine.SoundWave'/Game/PKH/Sound/Level3/SFX_FireAlarm.SFX_FireAlarm'" ) );
	if (SFX_FireAlarmRef.Object)
	{
		SFX_FireAlarm = SFX_FireAlarmRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundAttenuation> SA_FireAlarmRef( TEXT( "/Script/Engine.SoundAttenuation'/Game/PKH/Blueprints/Sound/SA_FireAlarm.SA_FireAlarm'" ) );
	if (SA_FireAlarmRef.Object)
	{
		SA_FireAlarm = SA_FireAlarmRef.Object;
	}

	static ConstructorHelpers::FObjectFinder<USoundBase> SFX_MissionClearRef( TEXT( "/Script/Engine.SoundWave'/Game/PKH/Sound/SFX_MissionClear.SFX_MissionClear'" ) );
	if (SFX_MissionClearRef.Object)
	{
		SFX_MissionClear = SFX_MissionClearRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<USoundBase> SFX_MissionFailRef( TEXT( "/Script/Engine.SoundWave'/Game/PKH/Sound/SFX_MissionFail.SFX_MissionFail'" ) );
	if (SFX_MissionFailRef.Object)
	{
		SFX_MissionFail = SFX_MissionFailRef.Object;
	}

	// Level
	LevelNames.Add(TEXT("Demo_Copy"));
	LevelNames.Add(TEXT("Level2_Test_Copy"));
	LevelNames.Add(TEXT("Level3"));
}

void APKHGameMode::BeginPlay()
{
	FString CurLevelName = UGameplayStatics::GetCurrentLevelName(GetWorld());
	if (CurLevelName == LevelNames[0])
	{
		LevelIdx = 1;
		CurQuest = EQuestType::Q1_FightWithMan; 
	}
	else if(CurLevelName == LevelNames[1])
	{
		LevelIdx = 2;
		CurQuest = EQuestType::Q4_PlantBombs;
	}
	else if (CurLevelName == LevelNames[2])
	{
		LevelIdx = 3;
		CurQuest = EQuestType::Q6_GetTheDisk;
	}
	
	// UI
	QuestGuideUI = CreateWidget<UQuestGuideWidget>(GetWorld(), QuestGuideUIClass);
	if (QuestGuideUI)
	{
		QuestGuideUI->AddToViewport();
		FTimerHandle GuideHandle;

		switch (LevelIdx)
		{
		case 1:
			QuestGuideUI->SetQuestGuideText(TEXT("오늘은 썩 기분이 거지같군. 누구 하나 잡고 시비라도 걸어야겠어."), 4.0f, true);
			GetWorldTimerManager().SetTimer( GuideHandle , FTimerDelegate::CreateLambda(
				[this]() {
					QuestGuideUI->SetQuestGuideText( TEXT( "전화중인 남자에게 시비를 거십시오." ) );
				} ) , 4.0f , false );
			break;
		case 2:
			QuestGuideUI->SetQuestGuideText(TEXT("폭탄을 설치하십시오."));
			break;
		case 3:
			QuestGuideUI->SetQuestGuideText(TEXT("좋아, 혼란한 틈을 타서 디스크를 훔치면 되겠군."), 4.0f, true);
			GetWorldTimerManager().SetTimer( GuideHandle , FTimerDelegate::CreateLambda(
				[this]() {
					QuestGuideUI->SetQuestGuideText( TEXT( "보안 디스크를 획득하십시오." ) );
				} ) , 4.0f , false );
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

	// Hp Bar
	if (LevelIdx == 1)
	{
		PlayerHpUI = CreateWidget<UPlayerHPBar>( GetWorld() , PlayerHpUIClass );
		if (PlayerHpUI)
		{
			PlayerHpUI->AddToViewport();
		}
	}

	// Timer
	GetWorldTimerManager().SetTimer(TimeHandle, FTimerDelegate::CreateLambda(
		[this]() {
			Seconds++;
		}), 1.0f, true);

	// BGM
	switch (LevelIdx)
	{
	case 1:
		
		break;
	case 2:
		
		break;
	case 3:
		BgmComps.Add( UGameplayStatics::SpawnSound2D( GetWorld() , BGM_Level3 , 0.3f ));
		BgmComps.Add(UGameplayStatics::SpawnSoundAtLocation( GetWorld() , SFX_FireAlarm , FVector(-3000, -538, 5200) , FRotator() , 0.15f , 1.0f, 0, SA_FireAlarm ));
		break;
	}
}

void APKHGameMode::SetQuestGuideText(FString GuideString, float DisplayTime, bool IsMonologue )
{
	QuestGuideUI->SetQuestGuideText(GuideString, DisplayTime, IsMonologue );
}

void APKHGameMode::UnsetQuestGuideText()
{
	QuestGuideUI->UnsetQuestGuideText();
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

void APKHGameMode::CountBomb()
{
	if (CurQuest != EQuestType::Q4_PlantBombs)
	{
		return;
	}

	BombCount++;
	if (BombCount == 3)
	{
		ClearCurQuest();
		SetQuestGuideText( TEXT( "폭탄은 모두 설치했군. 슬슬 나가야겠어." ) , 4.0f , true );

		FTimerHandle GuideHandle;
		GetWorldTimerManager().SetTimer( GuideHandle , FTimerDelegate::CreateLambda(
			[this]() {
				SetQuestGuideText( TEXT( "보안국 건물을 나간 뒤, 폭탄을 터뜨리십시오." ) );
			} ) , 4.0f , false );
	}
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

	// UI
	GameClearUI->SetClearUIText(Seconds, OxygenUI->GetOxygenRate(), KillCount);
	GameClearUI->SetVisibility(ESlateVisibility::Visible);

	// Sound
	for (int i = 0; i < BgmComps.Num(); i++)
	{
		BgmComps[i]->Stop();
	}
	UGameplayStatics::PlaySound2D(GetWorld(), SFX_MissionClear, 1.0f);

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

	// Sound
	for (int i = 0; i < BgmComps.Num(); i++)
	{
		BgmComps[i]->Stop();
	}
	UGameplayStatics::PlaySound2D( GetWorld() , SFX_MissionFail , 1.0f );

	// Game Over
	GameOverUI->SetFailReasonText(NewFailReasonString);
	GameOverUI->SetVisibility(ESlateVisibility::Visible);
	UGameplayStatics::SetGlobalTimeDilation(GetWorld(), 0.2f);
}

void APKHGameMode::OpenLevel(enum ELevelSelect NewLevel)
{
	QuestGuideUI->UnsetQuestGuideText();

	UP2JGameInstance* GI = Cast<UP2JGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()));
	if (GI)
	{
		GI->AddSeconds(Seconds);
	}

	uint8 Idx = (uint8)NewLevel;
	UGameplayStatics::OpenLevel(GetWorld(), LevelNames[Idx]);
}
