// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Car/AutoCar.h"
#include "Components/BoxComponent.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"

AAutoCar::AAutoCar()
{
	PrimaryActorTick.bCanEverTick = true;

	// Components
	BoxComp = CreateDefaultSubobject<UBoxComponent>( TEXT( "BoxComp" ) );
	SetRootComponent( BoxComp );
	BoxComp->SetCollisionEnabled( ECollisionEnabled::NoCollision );

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>( TEXT( "MeshComp" ) );
	MeshComp->SetupAttachment( BoxComp );
	MeshComp->SetRelativeScale3D( FVector( 0.7f ) );
	MeshComp->SetCollisionProfileName( TEXT( "BlockAll" ) );
	MeshComp->OnComponentHit.AddDynamic(this, &AAutoCar::OnPlayerHit );
}

void AAutoCar::BeginPlay()
{
	Super::BeginPlay();
	
	TargetRotation = GetActorRotation() + FRotator( 0 , 90 , 0 );
	if (TargetRotation.Yaw == 360)
	{
		TargetRotation.Yaw = 0;
	}
	IsRotating = false;

	CurMoveSpeed = MinMoveSpeed;
}

void AAutoCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		SetActorRotation(FMath::Lerp<FRotator>(GetActorRotation(), TargetRotation, DeltaTime));
		float TargetYaw = FMath::Abs(TargetRotation.Yaw - GetActorRotation().Yaw) < 90 ? TargetRotation.Yaw : TargetRotation.Yaw - 360;
		if (FMath::Abs(TargetYaw - GetActorRotation().Yaw) < 5)
		{
			SetActorRotation( TargetRotation );
			IsRotating = false;
		}
	}
	else
	{
		if (CurMoveSpeed < MaxMoveSpeed)
		{
			CurAccel += DeltaAccel * DeltaTime;
			CurMoveSpeed += CurAccel;
		}
		SetActorLocation( GetActorLocation() + GetActorRightVector() * CurMoveSpeed * DeltaTime );
	}
}

void AAutoCar::OnPlayerHit( UPrimitiveComponent* HitComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , FVector NormalImpulse , const FHitResult& Hit )
{
	APlayerZeroCharacter* Player = Cast<APlayerZeroCharacter>( OtherActor );
	if (nullptr == Player)
	{
		return;
	}
	
	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );
	if (nullptr == GameMode)
	{
		return;
	}

	if (CurMoveSpeed > 1000)
	{
		GameMode->GameOver( TEXT( "차에 치여 사망하였습니다." ) );
		Player->TakePlayerDamaged( 1000 );
	}
	else
	{
		Player->TakePlayerDamaged( 1 );
	}
}

void AAutoCar::StartRotation()
{
	TargetRotation = GetActorRotation() + FRotator( 0 , 90 , 0 );
	if (TargetRotation.Yaw == 360)
	{
		TargetRotation.Yaw = 0;
	}

	IsRotating = true;
	CurMoveSpeed = MinMoveSpeed;
	CurAccel = 0;
}
