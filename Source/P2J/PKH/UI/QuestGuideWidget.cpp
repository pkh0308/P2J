// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/QuestGuideWidget.h"
#include "Components/TextBlock.h"

UQuestGuideWidget::UQuestGuideWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
}

void UQuestGuideWidget::NativeConstruct()
{
}

void UQuestGuideWidget::SetQuestGuideText(FString GuideString, float DisplayTime, bool IsMonologue)
{
	if (GuideHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(GuideHandle);
	}

	if (IsMonologue)
	{
		GuideText->SetText(FText::FromString(FString::Printf(TEXT("\"%s\""), *GuideString)));
	}
	else
	{
		GuideText->SetText(FText::FromString( GuideString));
	}
	GuideText->SetVisibility(ESlateVisibility::Visible);

	if (DisplayTime > 0)
	{
		GetWorld()->GetTimerManager().SetTimer(GuideHandle, FTimerDelegate::CreateLambda(
			[this]() {
				GuideText->SetVisibility(ESlateVisibility::Hidden);
			}), DisplayTime, false);
	}
}

void UQuestGuideWidget::UnsetQuestGuideText()
{
	if (GuideHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(GuideHandle);
	}
	GuideText->SetVisibility(ESlateVisibility::Hidden);
}
