// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/DynamitePlace.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PlayerTwoCharacter.h"
#include "Dynamite.h"

// Sets default values
ADynamitePlace::ADynamitePlace()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	Trigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));
	SetRootComponent(Trigger);

	Trigger->SetCollisionProfileName(TEXT("CleanItem"));


}

// Called when the game starts or when spawned
void ADynamitePlace::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADynamitePlace::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADynamitePlace::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	Trigger->OnComponentBeginOverlap.AddDynamic(this, &ADynamitePlace::OnPlayer2Overlap);
}

//�׽�Ʈ�� �ڵ�. 
void ADynamitePlace::OnPlayer2Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerTwoCharacter* player = Cast<APlayerTwoCharacter>(OtherActor);

	UE_LOG(LogTemp, Warning, TEXT("DynamicTest"));
	if (player)
	{
		SetDynamite();
	}
}

//�÷��̾�2 �� Ʈ���� ��ġ�� overlap �Ǹ� ��Ŭ���϶�� ���� ���� -> ���� ��Ŭ�� ��, ��ź ��ġ
void ADynamitePlace::SetDynamite()
{
	FTransform t = Trigger->GetComponentTransform();
	GetWorld()->SpawnActor<ADynamite>(dynamiteFactory, t);
	UE_LOG(LogTemp, Warning, TEXT("DynamicTest1"));
}

