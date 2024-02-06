// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/DynamitePlace.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/BoxComponent.h"
#include "PlayerTwoCharacter.h"
#include "Dynamite.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../PKH/Game/PKHGameMode.h"

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

//테스트용 코드. 
void ADynamitePlace::OnPlayer2Overlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APlayerTwoCharacter* player = Cast<APlayerTwoCharacter>(OtherActor);
	APKHGameMode* gamemode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	gamemode->SetQuestGuideText(TEXT("E 키를 눌러 폭탄을 설치하시오."));

	UE_LOG(LogTemp, Warning, TEXT("DynamicTest"));
	if (player)
	{
		//SetDynamite();
	}
}

//플레이어2 가 트리거 위치로 overlap 되면 우클릭하라는 문구 나옴 -> 이후 우클릭 시, 폭탄 설치
void ADynamitePlace::SetDynamite()
{
	FTransform t = Trigger->GetComponentTransform();
	GetWorld()->SpawnActor<ADynamite>(dynamiteFactory, t);
	UE_LOG(LogTemp, Warning, TEXT("DynamicTest1"));
}

