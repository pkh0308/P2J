// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer/AnimNotify_PasserDamagedEnd.h"
#include "PKH/Passer/PasserBase.h"

void UAnimNotify_PasserDamagedEnd::Notify(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation)
{
	Super::Notify(MeshComp, Animation);

	APasserBase* Passer = Cast<APasserBase>(MeshComp->GetOwner());
	if (Passer)
	{
		Passer->OnDamagedEnd();
	}
}
