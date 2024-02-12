// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Item/Item_Disk.h"
#include "PKH/Game/PKHGameMode.h"
#include "Kismet/GameplayStatics.h"
#include "Components/BoxComponent.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/LevelSequence/Public/LevelSequencePlayer.h"

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

void AItem_Disk::BeginPlay()
{
	Super::BeginPlay();

	FMovieSceneSequencePlaybackSettings MovieSetting;
	ALevelSequenceActor* OutActor;
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer( GetWorld() , SequenceFactory , MovieSetting , OutActor );
}

void AItem_Disk::GetItem( APlayerZeroCharacter* InCharacter)
{
	Super::GetItem(InCharacter);

	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest(EQuestType::Q7_GetTheDisk))
	{
		GameMode->ClearCurQuest();
		SequencePlayer->Play();

		FTimerHandle MonoHandle;
		GetWorldTimerManager().SetTimer( MonoHandle, FTimerDelegate::CreateLambda(
			[GameMode]() {
				GameMode->SetQuestGuideText( TEXT( "좋아, 필요한 물건은 챙겼으니 얼른 나가야겠어." ), 4.0f, true );
			}), 4.0f, false);

		FTimerHandle GuideHandle;
		GetWorldTimerManager().SetTimer( GuideHandle , FTimerDelegate::CreateLambda(
			[GameMode]() {
				GameMode->SetQuestGuideText( TEXT( "보안국 건물에서 탈출하십시오." ) );
			} ) , 8.0f , false );
	}
}
