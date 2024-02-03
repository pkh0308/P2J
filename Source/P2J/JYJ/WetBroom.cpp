// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/WetBroom.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SkeletalMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/StaticMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PlayerTwoCharacter.h"

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

	/*
	ConstructorHelpers::FObjectFinder<USkeletalMesh> broomMesh(TEXT(""));
	if (broomMesh.Succeeded())
	{
		BroomstickComp->SetSkeletalMesh(broomMesh.Object);
	}
	*/
	


}

// Called when the game starts or when spawned
void AWetBroom::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWetBroom::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWetBroom::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &AWetBroom::OnCharacterOverlap);
}

void AWetBroom::OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	UE_LOG(LogTemp, Warning, TEXT("Broom test"));

	APlayerTwoCharacter* playerTwo = Cast<APlayerTwoCharacter>(OtherActor);

	if (playerTwo)
	{
		FName BroomSocket(TEXT("BroomSocket"));
		AttachToComponent(playerTwo->GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, BroomSocket);

	}
}

