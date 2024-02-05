// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/GameOverWidget.h"
#include "Components/TextBlock.h"

void UGameOverWidget::SetFailReasonText(FString NewFailReason)
{
	FailReasonText->SetText(FText::FromString(NewFailReason));
}
