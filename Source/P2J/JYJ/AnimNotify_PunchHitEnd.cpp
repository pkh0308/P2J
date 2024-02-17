// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/AnimNotify_PunchHitEnd.h"
#include "PlayerZeroCharacter.h"

void UAnimNotify_PunchHitEnd::Notify( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation )
{
	Super::Notify( MeshComp , Animation );

	if (MeshComp)
	{
		APlayerZeroCharacter* AttackPlayer = Cast<APlayerZeroCharacter>( MeshComp->GetOwner() );

		if (AttackPlayer)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Player attack2 TEST3" ) );
			//AttackPlayer->punchComp->SetCollisionProfileName( TEXT( "PlayerAttack" ) );
			AttackPlayer->bAvailableMove = true;

		}

	}
}