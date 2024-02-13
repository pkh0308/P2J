// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/ToiletTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

void AToiletTrigger::OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
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

	// Monologue & guide
	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest( EQuestType::Q4_PlantBombs ))
	{
		GameMode->ClearCurQuest();
	}

	FTimerHandle MonoHandle;
	GetWorldTimerManager().SetTimer( MonoHandle , FTimerDelegate::CreateLambda(
		[GameMode]() {
			GameMode->SetQuestGuideText( TEXT( "폭탄은 모두 설치했군. 슬슬 나가야겠어." ) , 4.0f , true );
		} ) , 4.0f , false );

	FTimerHandle GuideHandle;
	GetWorldTimerManager().SetTimer( GuideHandle , FTimerDelegate::CreateLambda(
		[GameMode]() {
			GameMode->SetQuestGuideText( TEXT( "보안국 건물을 나간 뒤, 폭탄을 터뜨리십시오." ) );
		} ) , 8.0f , false );
}
