// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/ElebatorEscapeTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void AElebatorEscapeTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (false == OtherActor->IsA<ACharacter>())
	{
		return;
	}

	PlaySequence();
	
	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (GameMode)
	{
		GameMode->SetHpBar( false );
		GameMode->StopOxygenTimer();

		FTimerHandle HpHandle;
		GetWorldTimerManager().SetTimer( HpHandle , FTimerDelegate::CreateLambda(
			[GameMode]() {
				GameMode->SetHpBar( true );
			} ) , 3.0f , false );
	}
}
