// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/UI/OxygenWidget.h"
#include "Components/ProgressBar.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void UOxygenWidget::NativeConstruct()
{
	CurTime = MaxTime;
	OxygenGuage->SetPercent((float)CurTime / MaxTime);
}

void UOxygenWidget::StartOxygenTimer()
{
	GetWorld()->GetTimerManager().SetTimer(OxygenHandle, this, &UOxygenWidget::UpdateTimer, 1.0f, true);
}

void UOxygenWidget::StopOxygenTimer()
{
	if (OxygenHandle.IsValid())
	{
		GetWorld()->GetTimerManager().ClearTimer(OxygenHandle);
	}
}

void UOxygenWidget::UpdateTimer()
{
	CurTime--;
	OxygenGuage->SetPercent((float)CurTime / MaxTime);

	// End Timer
	if (CurTime == 0)
	{
		GetWorld()->GetTimerManager().SetTimer(OxygenHandle, FTimerDelegate::CreateLambda(
			[&]() {
				GetWorld()->GetTimerManager().ClearTimer(OxygenHandle);
			}
		), 0.5f, false);

		APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
		if (GameMode)
		{
			GameMode->GameOver(TEXT("산소가 부족하여 사망하였습니다."));
		}
	}
}
