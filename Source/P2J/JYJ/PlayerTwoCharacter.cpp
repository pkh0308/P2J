// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerTwoCharacter.h"
#include "PlayerAnimInstance.h"
#include "Dynamite.h"
#include "DynamitePlace.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "MudActor.h"
#include "WetBroom.h"
#include "../PKH/Game/PKHGameMode.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"

APlayerTwoCharacter::APlayerTwoCharacter()
{
	
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player2/Ch01_nonPBR_Skeleton.Ch01_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}

	springArmComp->TargetArmLength = 130.f;
	springArmComp->SetWorldLocation( FVector( 0 , 0 , 130 ) );
	p1camComp->SetWorldRotation( FRotator( -15 , 0 , 0 ) ); 
	p1camComp->SetWorldLocation( FVector(0, 30, -30));

	//플레이어 2 걸음 속도 조절
	this->GetCharacterMovement()->MaxWalkSpeed = 300;
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

void APlayerTwoCharacter::NotifyActorBeginOverlap(AActor* OtherActor)
{
	if (OtherActor->IsA<ADynamitePlace>())
	{
		bBombQEnabled = true;
		dynamiteTransform = OtherActor->GetActorTransform();
	}
}

void APlayerTwoCharacter::Tick( float DeltaTime )
{
	Super::Tick( DeltaTime );
	if (dynamiteCnt == 3)
	{
		gamemode->SetQuestGuideText(TEXT("건물을 나가시오."));
	}

}

void APlayerTwoCharacter::cleanStart()
{
	PlayerAnim->PlayerCleanMontage();
	bCleanQEnabled = true;
	if (bCleanQEnabled)
	{
		//mud->mudDestroy();
	}

}

void APlayerTwoCharacter::cleanEnd()
{
	bCleanQEnabled = false;
}

void APlayerTwoCharacter::setupDynamite()
{
	if (bBombQEnabled)
	{
		GetWorld()->SpawnActor<ADynamite>(dynamiteFactory, dynamiteTransform);
		bBombQEnabled = false;
		dynamiteCnt++;
		
	}
}


