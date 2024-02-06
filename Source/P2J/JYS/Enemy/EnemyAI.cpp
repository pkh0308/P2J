// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/Enemy/EnemyAI.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"


// Sets default values
AEnemyAI::AEnemyAI()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// gunMeshComp 생성 및 배치
	gunMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("gunMeshComp"));
	
	ConstructorHelpers::FObjectFinder<UStaticMesh> tempGunMesh(TEXT("/Script/Engine.StaticMesh'/Game/JYS/Mesh/HandGun/pistol_Tauros/pistol_tauros.pistol_tauros'"));

	 // FName HandGunSocket(TEXT("HandGunSocket"));

	if (tempGunMesh.Succeeded())
	{
		gunMeshComp->SetStaticMesh(tempGunMesh.Object);
		gunMeshComp->SetRelativeLocationAndRotation(FVector(-4.838552, -14.091634, 7.870838), FRotator(32.259814, -56.247075, 210.800837));
		gunMeshComp->SetupAttachment(GetMesh(), TEXT("HandGunSocket"));
	}
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEnemyAI::OnActionFire()
{
	
	
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AEnemyAI::OnDamaged(int damage)
{
	if (isDead) 
	{
		return;
	}

	HP = HP - damage;
	if (HP <= 0)
	{
		OnDead();
	}
}

void AEnemyAI::OnDead()
{
	isDead = true;
}

void AEnemyAI::Attack()
{
	 FVector PlayerLoc = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	 FVector MyLoc = GetActorLocation();
	 FVector dir = PlayerLoc - MyLoc;
	 dir.Normalize();

	 // 불릿 스폰할 위치
	 FVector spawnLoc;
	 GetWorld()->SpawnActor<ABulletActor>(bulletFactory, FVector((37.000000, 0.000000, 51.000000)), FRotator(0));


}

