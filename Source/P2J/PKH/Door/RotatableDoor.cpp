// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Door/RotatableDoor.h"
#include "Components/BoxComponent.h"

ARotatableDoor::ARotatableDoor()
{
	PrimaryActorTick.bCanEverTick = true;

	// Components
	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	SetRootComponent(MeshComp);
	MeshComp->SetCollisionProfileName(TEXT("BlockAll"));

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	BoxComp->SetupAttachment(RootComponent);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ARotatableDoor::RotateDoor);
}

void ARotatableDoor::BeginPlay()
{
	Super::BeginPlay();
	
	IsTriggered = false;
}

void ARotatableDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (IsTriggered)
	{
		RootComponent->SetWorldRotation(FMath::RInterpTo(RootComponent->GetComponentRotation(), TargetRotation, DeltaTime, RotateSpeed));
	}
}

void ARotatableDoor::RotateDoor(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsTriggered)
	{
		return;
	}

	if (false == OtherActor->IsA<ACharacter>())
	{
		return;
	}

	IsTriggered = true;
}
