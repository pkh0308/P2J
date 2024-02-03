// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/WeaponActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"

// Sets default values
AWeaponActor::AWeaponActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//SMG11Y ·Îµå
	SMGMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("SMGMeshComp"));
	SMGMeshComp->SetupAttachment(RootComponent);

	ConstructorHelpers::FObjectFinder<UStaticMesh> smgMesh(TEXT("/Script/Engine.StaticMesh'/Game/JYJ/Models/FPS_Weapon_Bundle/Weapons/Meshes/SMG11/SM_SMG11_X.SM_SMG11_X'"));
	if (smgMesh.Succeeded())
	{
		SMGMeshComp->SetStaticMesh(smgMesh.Object);
		//SMGMeshComp->SetRelativeLocation(FVector(0, 80, 130));
		//SMGMeshComp->SetRelativeRotation(FRotator(0, 0, 90));
		SMGMeshComp->SetWorldScale3D(FVector(1.5f));
	}


}

// Called when the game starts or when spawned
void AWeaponActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeaponActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

