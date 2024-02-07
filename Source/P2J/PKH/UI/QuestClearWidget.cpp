// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/QuestClearWidget.h"
#include "Components/TextBlock.h"

void UQuestClearWidget::SetClearUIText(int32 ClearSeconds, float OxygenRate, int32 KillCount)
{
	// Time
	int m = ClearSeconds / 60;
	int s = ClearSeconds % 60;
	FString mm = m > 9 ? FString::Printf(TEXT("%d"), m) : FString::Printf(TEXT("0%d"), m);
	FString ss = s > 9 ? FString::Printf(TEXT("%d"), s) : FString::Printf(TEXT("0%d"), s);
	ClearTimeText->SetText(FText::FromString(FString::Printf(TEXT("임무 시간           %s:%s"), *mm, *ss)));
	// Oxygen
	int OxygenPercent = OxygenRate * 100;
	OxygenText->SetText(FText::FromString(FString::Printf(TEXT("남은 산소량          %d%%"), OxygenPercent )));
	// KillCount
	KillCountText->SetText(FText::FromString(FString::Printf(TEXT("처치한 요원            %d명"), KillCount)));
}
