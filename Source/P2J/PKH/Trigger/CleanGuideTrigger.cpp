// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/CleanGuideTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void ACleanGuideTrigger::OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	Super::OnPlayerOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );

	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}

	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if (nullptr == GameMode)
	{
		return;
	}
	if (false == GameMode->CheckCurQuest( EQuestType::Q4_PlantBombs ))
	{
		return;
	}

	GameMode->SetQuestGuideText( TEXT( "윗층에 올라가서 청소도구를 찾으시오." ) );
}
