// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/Enemy/EnemyAI.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/ArrowComponent.h"


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

	// EnemyFSM 컴포넌트 추가
	aiFSM = CreateDefaultSubobject<UAIFSM>(TEXT("aiFSM"));

	// firePosition 생성
	firePosition = CreateDefaultSubobject<UArrowComponent>(TEXT("FirePosition"));
	firePosition->SetupAttachment(RootComponent);
	firePosition->SetRelativeLocation(FVector(85,20,45));
}

// Called when the game starts or when spawned
void AEnemyAI::BeginPlay()
{
	Super::BeginPlay();
	// OnActionFire();
}

// Called every frame
void AEnemyAI::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	GetWorld()->GetTimerManager().SetTimer(fireTimerHandle, this, &AEnemyAI::Attack, 5.0f, true);
}


void AEnemyAI::OnActionFire()
{
	FTransform t = firePosition->GetComponentTransform();
	GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);
}

// Called to bind functionality to input
void AEnemyAI::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void AEnemyAI::OnDamaged(int damage)
{
	aiFSM->TakeDamage( damage );
	//attackState = true;
}

void AEnemyAI::OnDead()
{
	isDead = true;
	UE_LOG( LogTemp , Warning , TEXT( "die" ) );
}

void AEnemyAI::Attack()
{
	 FVector PlayerLoc = UGameplayStatics::GetPlayerPawn(GetWorld(), 0)->GetActorLocation();
	 FVector MyLoc = GetActorLocation();
	 FVector dir = PlayerLoc - MyLoc;
	 dir.Normalize();

	 // 불릿 스폰할 위치
	 //FVector spawnLoc;

	 FTransform t = gunMeshComp->GetSocketTransform(TEXT("FirePosition"));
	 GetWorld()->SpawnActor<ABulletActor>(bulletFactory, t);

	/*GetWorld()->GetTimerManager().ClearTimer(fireTimerHandle); */
	 
	 //GetWorld()->SpawnActor<ABulletActor>(bulletFactory, FVector((37.000000, 0.000000, 51.000000)), FRotator(0));

	 UE_LOG(LogTemp, Warning, TEXT("TEST1"));


}

