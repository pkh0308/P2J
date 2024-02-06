// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/ExplodeTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Interface/DestructibleDoorInterface.h"
#include "Kismet/GameplayStatics.h"

void AExplodeTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
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
	IsTriggered = true;

	// Destroy Door
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams Param;
	bool IsHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, Param, FCollisionShape::MakeSphere(50.0f));
	if (false == IsHit)
	{
		return;
	}

	for (int i = 0; i < OverlapResults.Num(); i++)
	{
		IDestructibleDoorInterface* DDoor = Cast<IDestructibleDoorInterface>(OverlapResults[i].GetActor());
		if (DDoor)
		{
			DDoor->DestroyActor();
		}
	}

	// Particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Explosion, GetActorLocation(), ExplodeRotation, ExplodeScale);

	// Camera Shake
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), ExplodeShakeClass, GetActorLocation(), InnerRadius, OuterRadius);
}
