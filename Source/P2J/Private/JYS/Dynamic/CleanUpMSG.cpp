// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/Dynamic/CleanUpMSG.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "../JYJ/PlayerTwoCharacter.h"
#include "../PKH/Game/PKHGameMode.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
// #include "Dynamite.h"

// Sets default values
ACleanUpMSG::ACleanUpMSG()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);


	Trigger->SetCollisionProfileName(TEXT("CleanUpMSG"));

}

// Called when the game starts or when spawned
void ACleanUpMSG::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ACleanUpMSG::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ACleanUpMSG::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ACleanUpMSG::OnPlayer2Overlap);
}

void ACleanUpMSG::OnPlayer2Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerTwoCharacter* player = Cast<APlayerTwoCharacter>(OtherActor);
	APKHGameMode* gamemode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	gamemode->SetQuestGuideText(TEXT("윗층에 올라가서 청소도구를 찾으시오."));

	UE_LOG(LogTemp, Warning, TEXT("CleanUpMSGTest"));
	if (player)
	{

	}
}

