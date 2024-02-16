// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Car/AutoCar.h"
#include "Components/BoxComponent.h"

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
}

void AAutoCar::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsRotating)
	{
		SetActorRotation(FMath::Lerp<FRotator>(GetActorRotation(), TargetRotation, DeltaTime ));
		if (FMath::Abs(TargetRotation.Yaw - GetActorRotation().Yaw) < 5)
		{
			SetActorRotation( TargetRotation );
			IsRotating = false;
		}
	}
	else
	{
		SetActorLocation( GetActorLocation() + GetActorRightVector() * MoveSpeed * DeltaTime );
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
}
