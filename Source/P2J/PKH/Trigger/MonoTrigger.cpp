// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/MonoTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"

void AMonoTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                   UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnPlayerOverlap(OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult);
	if(IsTriggered)
	{
		return;
	}
	IsTriggered = true;

	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}
	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if (nullptr == GameMode)
	{
		return;
	}

	GameMode->SetQuestGuideText( TEXT( "놈들이 내가 소방수가 아니라는걸 눈치챘군. 다 죽이면 그만이지만." ), 5.0f, true );
}
