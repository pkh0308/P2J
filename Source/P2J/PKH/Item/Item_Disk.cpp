// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Item/Item_Disk.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"

AItem_Disk::AItem_Disk()
{
	BoxComp->SetBoxExtent(FVector(16, 10, 1.5f));
	BoxComp->SetCollisionProfileName(TEXT("OverlapAll"));

	MeshComp->SetRelativeScale3D(FVector(0.3f));
	MeshComp->SetCollisionProfileName(TEXT("NoCollision"));

	static ConstructorHelpers::FObjectFinder<UStaticMesh> MeshRef(TEXT("/Script/Engine.StaticMesh'/Game/PKH/Mesh/Disk/Energy_battery.Energy_battery'"));
	if (MeshRef.Object)
	{
		MeshComp->SetStaticMesh(MeshRef.Object);
	}
}

void AItem_Disk::GetItem(ACharacter* InCharacter)
{
	Super::GetItem(InCharacter);

	UE_LOG(LogTemp, Log, TEXT("Player Get Disk"));

	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest(EQuestType::Q7_GetTheDisk))
	{
		GameMode->ClearCurQuest();
		GameMode->SetQuestGuideText(TEXT("보안국 건물에서 탈출하십시오."));
	}
}
