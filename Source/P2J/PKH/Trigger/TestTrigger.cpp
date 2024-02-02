// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/TestTrigger.h"
#include "PKH/Passer/PasserBase.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"

void ATestTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (OtherActor->IsA<APasserBase>())
	{
		return;
	}
	if (false == OtherActor->IsA<ACharacter>())
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
		PlaySequence();
	}
}
