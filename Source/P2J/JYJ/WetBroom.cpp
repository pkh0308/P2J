// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/WetBroom.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PlayerTwoCharacter.h"
#include "../PKH/Game/PKHGameMode.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "MudActor.h"

// Sets default values
AWetBroom::AWetBroom()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	BroomstickComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("BroomstickComp"));
	BroomstickComp->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(BroomstickComp);
	Trigger->SetCollisionProfileName(TEXT("CleanItem"));

	
	ConstructorHelpers::FObjectFinder<UStaticMesh> broomMesh(TEXT("/Script/Engine.StaticMesh'/Game/JYJ/Models/Broom.Broom'"));
	if (broomMesh.Succeeded())
	{
		BroomstickComp->SetStaticMesh(broomMesh.Object);
	}


}

// Called when the game starts or when spawned
void AWetBroom::BeginPlay()
{
	Super::BeginPlay();

	nextQuest = true;
	
}

// Called every frame
void AWetBroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	player2->bCleanQEnabled = this->bCleanQEnabled;

}

void AWetBroom::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWetBroom::OnCharacterOverlap);
}

void AWetBroom::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerTwoCharacter* playerTwo = Cast<APlayerTwoCharacter>(OtherActor);
	APKHGameMode* gamemode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	//다음 퀘스트 안내 문구
	if (nextQuest)
	{
		gamemode->SetQuestGuideText(TEXT("복도 바닥의 얼룩을 닦으십시오."));
	}

	if (playerTwo)
	{
		//플레이어의 메쉬에 빗자루 붙임
		FName BroomSocket(TEXT("BroomSocket"));
		AttachToComponent(playerTwo->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BroomSocket);
		//bCleanQEnabled = true;
		//playerTwo->bCleanQEnabled = this->bCleanQEnabled;
		this->bCleanQEnabled = playerTwo->bCleanQEnabled;
		nextQuest = false;
	}

}

void AWetBroom::OnMudOverlap( UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	
	/*
	AMudActor* mud = Cast<AMudActor>(OtherActor);

	UE_LOG(LogTemp,Warning, TEXT("clean test1"));
	if ( bCleanQEnabled )
	{
		UE_LOG( LogTemp , Warning , TEXT( "clean test2" ) );
		OtherActor->Destroy();
	}
	*/
}

