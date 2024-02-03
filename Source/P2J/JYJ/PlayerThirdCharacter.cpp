// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerThirdCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/PrimitiveComponent.h"
#include "WeaponActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"

APlayerThirdCharacter::APlayerThirdCharacter()
{
	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.Skeleton'/Game/JYJ/Mesh/Player3/Ch35_nonPBR_Skeleton.Ch35_nonPBR_Skeleton'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}

	//SMG11Y �ε�
	/*
	SMGMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMGMeshComp"));
	SMGMeshComp->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<UStaticMesh> smgMesh(TEXT("/Script/Engine.StaticMesh'/Game/JYJ/Models/FPS_Weapon_Bundle/Weapons/Meshes/SMG11/SM_SMG11_X.SM_SMG11_X'"));
	if (smgMesh.Succeeded())
	{
		SMGMeshComp->SetStaticMesh(smgMesh.Object);
		SMGMeshComp->SetRelativeLocation(FVector(0, 80, 130));
		SMGMeshComp->SetRelativeRotation(FRotator(0,0,90));
		SMGMeshComp->SetWorldScale3D(FVector(1.5f));
	}
	*/

}

void APlayerThirdCharacter::BeginPlay()
{
	Super::BeginPlay();

	

}

void APlayerThirdCharacter::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Pressed, this, &APlayerThirdCharacter::ZoomIn);
	PlayerInputComponent->BindAction(TEXT("Zoom"), IE_Released, this, &APlayerThirdCharacter::ZoomOut);
	PlayerInputComponent->BindAction(TEXT("Shooting"), IE_Pressed, this, &APlayerThirdCharacter::OnActionFire);
	PlayerInputComponent->BindAction(TEXT("SMG11Y"), IE_Pressed, this, &APlayerThirdCharacter::OnActionChooseSMG11);


}

void APlayerThirdCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Zoom();
}

void APlayerThirdCharacter::Zoom()
{
	//���������� �̿��ؼ� ���� FOV�� targetFOV���� �����ϰ� �ϰ� �ʹ�.
	p1camComp->FieldOfView = FMath::Lerp<float>(p1camComp->FieldOfView, targetFOV, GetWorld()->GetDeltaSeconds() * 10);
}

void APlayerThirdCharacter::ZoomIn()
{
	targetFOV = 50;
	springArmComp->SetRelativeLocation(FVector( 0, 40, 90));
	//GetMesh()->SetRelativeLocation(FVector(-30, 0, -90));
}

void APlayerThirdCharacter::ZoomOut()
{
	targetFOV = 90;
	springArmComp->SetRelativeLocation(FVector(0, 0, 90));
	//GetMesh()->SetRelativeLocation(FVector(0, 0, -90));
}

void APlayerThirdCharacter::OnActionChooseSMG11()
{
	//SMGMeshComp->SetVisibility(true);
	AttachWeapon(Gun);
	//ZoomIn();
}

void APlayerThirdCharacter::OnActionFire()
{
	FHitResult outhit;
	FVector start = p1camComp->GetComponentLocation();
	FVector end = start + (p1camComp->GetForwardVector() * 100000);
	FCollisionQueryParams params;
	params.AddIgnoredActor(this);	//�÷��̾� ���� ��û

	bool breturnValue = GetWorld()->LineTraceSingleByChannel(outhit, start, end, ECollisionChannel::ECC_Visibility, params);

	if (breturnValue)
	{
		DrawDebugLine(GetWorld(), outhit.TraceStart, outhit.ImpactPoint, FColor::Red, false, 10);

		UPrimitiveComponent* hitComp = outhit.GetComponent();

		if (hitComp && hitComp->IsSimulatingPhysics())
		{
			//�� ������Ʈ���� ���� ���ϰ� �ʹ�.
			FVector tmp = end - start;
			hitComp->AddForce(tmp.GetSafeNormal() * 500000 * hitComp->GetMass());
		}

		//�ε��� ���� expVFX�� �����ؼ� ��ġ�ϰ� �ʹ�.
		UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), expVFX, outhit.ImpactPoint);


	}

}

void APlayerThirdCharacter::AttachWeapon(TSubclassOf<AWeaponActor> Weapon)
{

	UE_LOG(LogTemp, Warning, TEXT("test1"));
	if (Weapon) {

		//weapon�� ���� ������ ��� �ְ� ���� ��ü�� �����Ǿ� ���� ����
		UE_LOG(LogTemp, Warning, TEXT("test2"));
		AActor* SpawnWeapon = GetWorld()->SpawnActor<AWeaponActor>(FVector::ZeroVector, FRotator::ZeroRotator);
		//AActor* SpawnWeapon = get
		
		//������ ������ socket �̸��� ���� socket ������ �����´�.
		const USkeletalMeshSocket* WeaponSocket = GetMesh()->GetSocketByName("RifleGunSocket");

		if (WeaponSocket && SpawnWeapon)
		{
			UE_LOG(LogTemp, Warning, TEXT("test3"));
			//WeaponSocket->AttachActor(SpawnWeapon, this->GetMesh());
			//WeaponSocket->AttachActor(SpawnWeapon, WeaponSocket);
		}
	}
}
