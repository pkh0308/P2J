// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/EnterBuildingTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void AEnterBuildingTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}

	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest(EQuestType::Q3_EnterBuilding))
	{
		GameMode->ClearCurQuest();
		GameMode->ShowFadeOut();

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
			[GameMode]() {
				GameMode->OpenLevel(ELevelSelect::Level2);
			}), 3.0f, false);
	}
}
