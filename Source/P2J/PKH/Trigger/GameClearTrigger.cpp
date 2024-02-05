// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/GameClearTrigger.h"
#include "PKH/Game/PKHGameMode.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "Kismet/GameplayStatics.h"

void AGameClearTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (IsTriggered)
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

	IsTriggered = true;
	GameMode->GameClear();
}
