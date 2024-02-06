// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/MudActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PlayerTwoCharacter.h"
#include "WetBroom.h"
#include "../PKH/Game/PKHGameMode.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"

// Sets default values
AMudActor::AMudActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Mud = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mud"));
	
	Mud->SetupAttachment(RootComponent);

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	Trigger->SetupAttachment(Mud);
	Trigger->SetCollisionProfileName(TEXT("CleanItem"));


	/*
	ConstructorHelpers::FObjectFinder<UStaticMesh> mudMesh(TEXT("/Script/Engine.StaticMesh'/Game/JYJ/Models/Ax_Weapon/test.test'"));
	if (mudMesh.Succeeded())
	{
		Mud->SetStaticMesh(mudMesh.Object);
	}
	*/


}

// Called when the game starts or when spawned
void AMudActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMudActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMudActor::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AMudActor::OnCharacterOverlap);
}

void AMudActor::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("mud test1"));

	//APlayerTwoCharacter* playerTwo = Cast<APlayerTwoCharacter>(OtherActor);
	AWetBroom* broom = Cast<AWetBroom>(OtherActor);
	APKHGameMode* gamemode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	if (broom )
	{
		gamemode->SetQuestGuideText(TEXT("우클릭으로 얼룩을 지우십시오."));

		if(broom->bCleanQEnabled )
		{
			UE_LOG(LogTemp, Warning, TEXT("mud test2"));
			this->Destroy(true);
		}
		

	}

}

