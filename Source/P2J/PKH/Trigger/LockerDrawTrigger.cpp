// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/LockerDrawTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"

void ALockerDrawTrigger::OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	Super::OnPlayerOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );

	if (IsTriggered)
	{
		return;
	}

	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}

	IsTriggered = true;
	PlaySequence();
}
