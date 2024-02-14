// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/SequenceTrigger.h"
#include "Components/BoxComponent.h"
#include "../../../../../../../Source/Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "PKH/Passer/PasserBase.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"

ASequenceTrigger::ASequenceTrigger()
{
	PrimaryActorTick.bCanEverTick = false;

	BoxComp = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComp"));
	SetRootComponent(BoxComp);
	BoxComp->SetCollisionProfileName(TEXT("SequenceTrigger"));
	BoxComp->OnComponentBeginOverlap.AddDynamic(this, &ASequenceTrigger::OnPlayerOverlap);
	BoxComp->SetBoxExtent(FVector(100));
}

void ASequenceTrigger::BeginPlay()
{
	Super::BeginPlay();
	
	FMovieSceneSequencePlaybackSettings MovieSetting;
	ALevelSequenceActor* OutActor;
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), SequenceFactory, MovieSetting, OutActor);
}

void ASequenceTrigger::OnSequenceFinished()
{
	
}

void ASequenceTrigger::OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}

void ASequenceTrigger::PlaySequence()
{
	SequencePlayer->Play();
}
