// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/LockerDrawTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

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

	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if (nullptr == GameMode)
	{
		return;
	}

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer( Handle , FTimerDelegate::CreateLambda(
		[GameMode]() {
			GameMode->CountBomb();
		} ) , 6.5f , false );
}

void ALockerDrawTrigger::OnSequenceFinished()
{
	
}
