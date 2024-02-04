// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Door/DestructibleDoor.h"
#include "Components/BoxComponent.h"

// Sets default values
ADestructibleDoor::ADestructibleDoor()
{
	PrimaryActorTick.bCanEverTick = false;

	// Components
	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("BlockAll"));

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(BoxComp);
	MeshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

void ADestructibleDoor::BeginPlay()
{
	Super::BeginPlay();
	
}

void ADestructibleDoor::DestroyActor()
{
	BoxComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	MeshComp->SetVisibility(false);
}
