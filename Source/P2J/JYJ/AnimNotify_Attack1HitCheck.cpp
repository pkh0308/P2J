// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/AnimNotify_Attack1HitCheck.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Animation/AnimSequenceBase.h"
#include "AnimAAttackInterface.h"

void UAnimNotify_Attack1HitCheck::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	if (MeshComp)
	{
		APlayerZeroCharacter* AttackPawn = Cast<APlayerZeroCharacter>(MeshComp->GetOwner());

		if (AttackPawn)
		{
			//AttackPawn->punchComp->SetCollisionProfileName(TEXT("PlayerAttack"));
			AttackPawn->punchComp->SetCollisionEnabled(ECollisionEnabled::QueryAndPhysics);
		}
		
	}
}
