﻿// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerThirdCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "WeaponActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "PlayerAnimInstance.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Blueprint/UserWidget.h"
#include "../JYS/Enemy/EnemyAI.h"
#include "../PKH/Game/PKHGameMode.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SpotLightComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"

APlayerThirdCharacter::APlayerThirdCharacter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player3/Ch35_nonPBR_Skeleton.Ch35_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}

	//Player LightCookie settings
	lightCookie = CreateDefaultSubobject<USpotLightComponent>(TEXT("lightCookie"));
	lightCookie->SetupAttachment( GetMesh() ); 
	lightCookie->SetRelativeLocation( FVector( 10, 15, 140) );
	lightCookie->SetWorldRotation( FRotator( 0, 90, 0) );

	//Player InsideLight settings
	playerLight = CreateDefaultSubobject<USpotLightComponent>(TEXT("playerLight"));
	playerLight->SetupAttachment( GetCapsuleComponent()); 
	playerLight->SetRelativeLocation(FVector(-130, 0, 50));
	playerLight->SetIntensity(7000);
	playerLight->SetAttenuationRadius(500);

	//Player3 Camera settings
	springArmComp->TargetArmLength = 130.f;
	springArmComp->SetWorldLocation( FVector( 0 , 0 , 130 ) );
	p1camComp->SetWorldRotation( FRotator( -15 , 0 , 0 ) );
	p1camComp->SetWorldLocation( FVector( 0 , 30 , -30 ) );

}

void APlayerThirdCharacter::BeginPlay()
{
	Super::BeginPlay();
	bValidRifle = false;
	bAttack		= false;

	crossHairUI = CreateWidget(GetWorld(), crossHairFactory);
	crossHairUI->AddToViewport();
	crossHairUI->SetVisibility(ESlateVisibility::Hidden);


}

void APlayerThirdCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Zoom / Clean"), IE_Pressed, this, &APlayerThirdCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("Zoom / Clean"), IE_Released, this, &APlayerThirdCharacter::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("Shooting"), IE_Pressed, this, &APlayerThirdCharacter::OnActionFire);
	PlayerInputComponent->BindAction(TEXT("SMG11Y"), IE_Pressed, this, &APlayerThirdCharacter::OnActionChooseSMG11);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Pressed, this, &APlayerThirdCharacter::OnActionCrouchStart);
	PlayerInputComponent->BindAction(TEXT("Crouch"), IE_Released, this, &APlayerThirdCharacter::OnActionCrouchEnd);


}

void APlayerThirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Zoom();
}

void APlayerThirdCharacter::Zoom()
{
	//선형보간을 이용해서 현재 FOV를 targetFOV값에 근접하게 하고 싶다.
	p1camComp->FieldOfView = FMath::Lerp<float>(p1camComp->FieldOfView, targetFOV, GetWorld()->GetDeltaSeconds() * 10);
}

void APlayerThirdCharacter::ZoomIn()
{
	if (bValidRifle)
	{
		targetFOV = 70;
		bOnZoomRifle = true;
		crossHairUI->SetVisibility(ESlateVisibility::Visible);
		springArmComp->SetRelativeLocation(FVector( 0, 40, 130));

		//조준 시, 플레이어 조준점으로 회전
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void APlayerThirdCharacter::ZoomOut()
{
	targetFOV = 90;
	bOnZoomRifle = false;
	springArmComp->SetRelativeLocation(FVector(0, 0, 130));
	crossHairUI->SetVisibility(ESlateVisibility::Hidden);

	//조준 X, 상태 원복
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
}

void APlayerThirdCharacter::OnActionChooseSMG11()
{
	//SMGMeshComp->SetVisibility(true);
	AttachWeapon(Gun);
	bAttack = false;
	//bValidRifle = true;
	//ZoomIn();
}

void APlayerThirdCharacter::OnActionFire()
{
	bAttack = true;
	if(bAttack == true && bValidRifle == true)
	{ 
		FHitResult outhit;
		FVector start = p1camComp->GetComponentLocation();
		FVector end = start + (p1camComp->GetForwardVector() * 100000);
		FCollisionQueryParams params;
		params.AddIgnoredActor(this);	//플레이어 제외 요청

		if (nullptr == PlayerAnim) return;
		PlayerAnim->PlayerRifleFireMontage();
		bool breturnValue = GetWorld()->LineTraceSingleByChannel(outhit, start, end, ECollisionChannel::ECC_Pawn , params);

		if (breturnValue)
		{
			
			//DrawDebugLine(GetWorld(), outhit.TraceStart, outhit.ImpactPoint, FColor::Red, false, 0.2f);
			//FTransform t = GetMesh()->GetSocketTransform( TEXT("RifleGunSocket") );
			//triggerSocket
			FTransform t = Rifle->SMGMeshComp->GetSocketTransform( TEXT( "triggerSocket" ) );

			DrawDebugLine( GetWorld() , t.GetLocation() , outhit.ImpactPoint , FColor::Silver , false , 0.2f);
			
			UPrimitiveComponent* hitComp = outhit.GetComponent();

			AEnemyAI* enemy2 = Cast<AEnemyAI>( outhit.GetActor());
			
			if ( enemy2 )
			{
				//그 컴포넌트한테 힘을 가하고 싶다.
				FVector tmp = end - start;
				//hitComp->AddForce(tmp.GetSafeNormal() * 500000 * hitComp->GetMass());
				//enemy2->Destroy();
				UE_LOG(LogTemp, Warning, TEXT("enemy2 attack"));
				enemy2->OnDamaged(1);

			}

			//부딪힌 곳에 expVFX를 생성해서 배치하고 싶다.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outhit.ImpactPoint);

			bAttack = false;
		}
	}

}

void APlayerThirdCharacter::AttachWeapon(TSubclassOf<AWeaponActor> WeaponFactory)
{
	if (WeaponFactory) {
		//weapon에 무기 정보만 담겨 있고 실제 객체는 생성되어 있지 않음
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("RifleGunSocket");
		Rifle = GetWorld()->SpawnActor<AWeaponActor>(FVector::ZeroVector, FRotator::ZeroRotator);


		WeaponSocket->AttachActor( Rifle , GetMesh());
		bValidRifle = true;
		
	}
}

void APlayerThirdCharacter::OnActionCrouchStart()
{
	PlayerAnim->bCrouch = true;
}

void APlayerThirdCharacter::OnActionCrouchEnd()
{
	PlayerAnim->bCrouch = false;
}

