// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerTwoCharacter.h"
#include "PlayerAnimInstance.h"
#include "Dynamite.h"
#include "DynamitePlace.h"

APlayerTwoCharacter::APlayerTwoCharacter()
{
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player2/Ch01_nonPBR_Skeleton.Ch01_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}
}

void APlayerTwoCharacter::BeginPlay()
{
	Super::BeginPlay();

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

void APlayerTwoCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Zoom / Clean"), IE_Pressed, this, &APlayerTwoCharacter::cleanStart);
	PlayerInputComponent->BindAction(TEXT("Zoom / Clean"), IE_Released, this, &APlayerTwoCharacter::cleanEnd);
	PlayerInputComponent->BindAction(TEXT("Quest"), IE_Pressed, this, &APlayerTwoCharacter::setupDynamite);


}

void APlayerTwoCharacter::cleanStart()
{
	UE_LOG(LogTemp, Warning, TEXT("TEST PLAYER2"));
	PlayerAnim->PlayerCleanMontage();
}

void APlayerTwoCharacter::cleanEnd()
{
	
}


void APlayerTwoCharacter::setupDynamite()
{
	//ADynamitePlace* bombPlace = Cast<ADynamitePlace>(bombPlace);
	//bombPlace->SetDynamite();

}

