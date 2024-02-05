// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/ElebatorEscapeTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"

void AElebatorEscapeTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent, OtherActor, OtherComp, OtherBodyIndex, bFromSweep, SweepResult);

	if (false == OtherActor->IsA<ACharacter>())
	{
		return;
	}

	PlaySequence();
}
