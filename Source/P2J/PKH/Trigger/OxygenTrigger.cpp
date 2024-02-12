// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/OxygenTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void AOxygenTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (IsTriggered)
	{
		return;
	}
	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}
	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	GameMode->StartOxygenTimer();
	GameMode->SetQuestGuideText( TEXT( "여기서부턴 화재가 심하군. 빠르게 탈출해야겠어." ) , 4.0f , true );
}
