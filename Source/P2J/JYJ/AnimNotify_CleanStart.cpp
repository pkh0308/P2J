// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/AnimNotify_CleanStart.h"
#include "PlayerZeroCharacter.h"

void UAnimNotify_CleanStart::Notify( USkeletalMeshComponent* MeshComp , UAnimSequenceBase* Animation )
{
	Super::Notify( MeshComp , Animation );

	if (MeshComp)
	{
		APlayerZeroCharacter* player = Cast<APlayerZeroCharacter>( MeshComp->GetOwner() );

		if (player)
		{
			player->bAvailableMove = false;

		}

	}
}
