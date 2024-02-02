// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Item/Item_IDCard.h"
#include "Components/BoxComponent.h"
#include "KIsmet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"

AItem_IDCard::AItem_IDCard()
{
	BoxComp->SetBoxExtent(FVector(16, 10, 1.5f));
	BoxComp->SetCollisionProfileName(TEXT("IDCard"));
	BoxComp->SetSimulatePhysics(true);

	MeshComp->SetRelativeScale3D(FVector(0.35f));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));
	MeshComp->SetSimulatePhysics(false);

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/PKH/Mesh/IDCard/Card.Card'"));
	if (MeshRef.Object)
	{
		MeshComp->SetStaticMesh(MeshRef.Object);
	}
}

void AItem_IDCard::GetItem(ACharacter* InCharacter)
{
	Super::GetItem(InCharacter);

	UE_LOG(LogTemp, Log, TEXT("Player Get ID card"));

	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest(EQuestType::Q2_GetIDCard))
	{
		GameMode->ClearCurQuest();
	}
}
