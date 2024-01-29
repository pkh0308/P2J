// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/AnimNotify_PasserAttackEnd.h"
#include "PKH/Passer/PasserBase.h"

void UAnimNotify_PasserAttackEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	APasserBase* Passer = Cast<APasserBase>(MeshComp->GetOwner());
	if (Passer)
	{
		Passer->EndAttack();
	}
}