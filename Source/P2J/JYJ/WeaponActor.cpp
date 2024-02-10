// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/WeaponActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//SMG11Y 로드
	SMGMeshComp = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("SMGMeshComp"));
	SMGMeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> smgMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/JYJ/Models/FPS_Weapon_Bundle/Weapons/Meshes/SMG11/SK_SMG11_Nostock_Y.SK_SMG11_Nostock_Y'"));
	if (smgMesh.Succeeded())
	{
		SMGMeshComp->SetSkeletalMesh(smgMesh.Object);
		SMGMeshComp->SetRelativeLocation(FVector(3, -1, 2));
		//(Pitch=40.000000,Yaw=-100.000000,Roll=80.000000)
		SMGMeshComp->SetRelativeRotation(FRotator(40, -100, 80));
		SMGMeshComp->SetWorldScale3D(FVector(1.5f));
	}

	start = SMGMeshComp->GetSocketLocation("triggerSocket");

}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
/*
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}
*/

