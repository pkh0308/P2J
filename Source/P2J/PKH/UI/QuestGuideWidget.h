// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "QuestGuideWidget.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UQuestGuideWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UQuestGuideWidget(const FObjectInitializer& ObjectInitializer);

protected:
	virtual void NativeConstruct() override;

// Widget
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> GuideText;

	FTimerHandle GuideHandle;

public:
	void SetQuestGuideText(FString GuideString, float DisplayTime = 5.0f, bool IsMonologue = false);

	void UnsetQuestGuideText();
};
