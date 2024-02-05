// Fill out your copyright notice in the Description page of Project Settings.


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

APlayerThirdCharacter::APlayerThirdCharacter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player3/Ch35_nonPBR_Skeleton.Ch35_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}

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
	targetFOV = 50;
	bOnZoomRifle = true;
	crossHairUI->SetVisibility(ESlateVisibility::Visible);
	springArmComp->SetRelativeLocation(FVector( 0, 40, 90));
	//GetMesh()->SetRelativeLocation(FVector(-30, 0, -90));
}

void APlayerThirdCharacter::ZoomOut()
{
	targetFOV = 90;
	bOnZoomRifle = false;
	springArmComp->SetRelativeLocation(FVector(0, 0, 90));
	crossHairUI->SetVisibility(ESlateVisibility::Hidden);
	//GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
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
		bool breturnValue = GetWorld()->LineTraceSingleByChannel(outhit, start, end, ECollisionChannel::ECC_Visibility, params);

		if (breturnValue)
		{
			DrawDebugLine(GetWorld(), outhit.TraceStart, outhit.ImpactPoint, FColor::Red, false, 10);
			UPrimitiveComponent* hitComp = outhit.GetComponent();

			if (hitComp && hitComp->IsSimulatingPhysics())
			{
				//그 컴포넌트한테 힘을 가하고 싶다.
				FVector tmp = end - start;
				hitComp->AddForce(tmp.GetSafeNormal() * 500000 * hitComp->GetMass());
			}

			//부딪힌 곳에 expVFX를 생성해서 배치하고 싶다.
			UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outhit.ImpactPoint);

			bAttack = false;
		}
	}

}

void APlayerThirdCharacter::AttachWeapon(TSubclassOf<AWeaponActor> Weapon)
{
	//PlayerAnim->PlayerRifleFireMontage();
	if (Weapon) {
		//weapon에 무기 정보만 담겨 있고 실제 객체는 생성되어 있지 않음
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("RifleGunSocket");
		AWeaponActor* weapon = GetWorld()->SpawnActor<AWeaponActor>(FVector::ZeroVector, FRotator::ZeroRotator);

		if (weapon)
		{
			WeaponSocket->AttachActor(weapon, GetMesh());
			bValidRifle = true;
		}
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

