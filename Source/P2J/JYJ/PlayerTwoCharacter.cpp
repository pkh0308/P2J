// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerTwoCharacter.h"

APlayerTwoCharacter::APlayerTwoCharacter()
{
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player2/Ch01_nonPBR_Skeleton.Ch01_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}
}
