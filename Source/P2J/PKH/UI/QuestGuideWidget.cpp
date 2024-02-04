// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/QuestGuideWidget.h"
#include "Components/TextBlock.h"

UQuestGuideWidget::UQuestGuideWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UQuestGuideWidget::NativeConstruct()
{
}

void UQuestGuideWidget::SetQuestGuideText(FString GuideString, float DisplayTime)
{
	if (GuideHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(GuideHandle);
	}

	GuideText->SetText(FText::FromString(GuideString));
	GuideText->SetVisibility(ESlateVisibility::Visible);

	GetWorld()->GetTimerManager().SetTimer(GuideHandle, FTimerDelegate::CreateLambda(
		[this]() {
			GuideText->SetVisibility(ESlateVisibility::Hidden);
		}), DisplayTime, false);
}
