// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Bomb/ThrowableBomb.h"
#include "Components/BoxComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "PKH/Interface/DestructibleDoorInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Particles/ParticleSystem.h"

// Sets default values
AThrowableBomb::AThrowableBomb()
{
	PrimaryActorTick.bCanEverTick = false;

	// Components
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("BlockAll"));
	BoxComp->OnComponentHit.AddDynamic(this, &AThrowableBomb::OnBoxCompHit);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);

	ProjectileComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileComp"));
	ProjectileComp->ProjectileGravityScale = 0;
	ProjectileComp->InitialSpeed = 2000;
	ProjectileComp->MaxSpeed = 2000;
	ProjectileComp->bShouldBounce = false;

	// VFX
	static ConstructorHelpers::FObjectFinder<UParticleSystem> ParticleRef(TEXT("/Script/Engine.ParticleSystem'/Game/Realistic_Starter_VFX_Pack_Vol2/Particles/Explosion/P_Explosion_Big_B.P_Explosion_Big_B'"));
	if (ParticleRef.Object)
	{
		VFX_Explosion = ParticleRef.Object;
	}
}

void AThrowableBomb::BeginPlay()
{
	Super::BeginPlay();
	
}

void AThrowableBomb::OnBoxCompHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	ProjectileComp->Velocity = FVector::Zero();
}

void AThrowableBomb::ThrowBomb(FVector Direction, float DelayTime)
{
	ProjectileComp->Velocity = Direction * ProjectileComp->MaxSpeed;

	FTimerHandle Handle;
	GetWorldTimerManager().SetTimer(Handle, this, &AThrowableBomb::Explode, DelayTime, false);
}

void AThrowableBomb::Explode()
{
	// Particle
	UGameplayStatics::SpawnEmitterAtLocation(GetWorld(), VFX_Explosion, GetActorLocation(), FRotator::ZeroRotator, FVector(1.0f));

	// Shake
	UGameplayStatics::PlayWorldCameraShake(GetWorld(), BombShakeClass, GetActorLocation(), InnerRadius, OuterRadius);

	// Sound
	

	// Destroy Door
	TArray<FOverlapResult> OverlapResults;
	FCollisionObjectQueryParams Param;
	bool IsHit = GetWorld()->OverlapMultiByObjectType(OverlapResults, GetActorLocation(), FQuat::Identity, Param, FCollisionShape::MakeSphere( ExplodeRadius ));
	if (false == IsHit)
	{
		return;
	}

	for (int i = 0; i < OverlapResults.Num(); i++)
	{
		IDestructibleDoorInterface* DDoor = Cast<IDestructibleDoorInterface>(OverlapResults[i].GetActor());
		if (DDoor)
		{
			DDoor->DestroyActor();
		}
	}

	Destroy();
}
