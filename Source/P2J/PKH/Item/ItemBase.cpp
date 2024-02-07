// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Item/ItemBase.h"
#include "Components/BoxComponent.h"
#include "PKH/Passer/PasserBase.h"
#include "JYJ/PlayerZeroCharacter.h"

AItemBase::AItemBase()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &AItemBase::OnPlayerBeginOverlap);

	MeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("MeshComp"));
	MeshComp->SetupAttachment(RootComponent);
}

void AItemBase::BeginPlay()
{
	Super::BeginPlay();
	
}

void AItemBase::OnPlayerBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerZeroCharacter* PlayerCharacter = Cast<APlayerZeroCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		GetItem(PlayerCharacter);
	}
}

void AItemBase::SetActive(bool ActiveSelf)
{
	if (ActiveSelf)
	{
		BoxComp->SetCollisionProfileName(TEXT("Item"));
		MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
		MeshComp->SetVisibility(true);
	}
	else
	{
		BoxComp->SetCollisionProfileName(TEXT("NoCollision"));
		MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
		MeshComp->SetVisibility(false); 
	}
}

void AItemBase::GetItem(APlayerZeroCharacter* InCharacter)
{
	
}

