// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/AnimNotify_PunchEnd.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"

void UAnimNotify_PunchEnd::Notify( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation )
{
	Super::Notify( MeshComp , Animation );
	UE_LOG( LogTemp , Warning , TEXT( "Player attack2 TEST1" ) );

	if (MeshComp)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Player attack2 TEST2" ) );
		APlayerZeroCharacter* AttackPlayer = Cast<APlayerZeroCharacter>( MeshComp->GetOwner() );

		if (AttackPlayer)
		{
			UE_LOG( LogTemp , Warning , TEXT( "Player attack2 TEST3" ) );
			//AttackPlayer->punchComp->SetCollisionProfileName( TEXT( "PlayerAttack" ) );
			AttackPlayer->punchComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		}

	}
}
