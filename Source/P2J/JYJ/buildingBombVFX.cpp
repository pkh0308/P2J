// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/buildingBombVFX.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Particles/ParticleSystem.h"

// Sets default values
AbuildingBombVFX::AbuildingBombVFX()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bombVFX = CreateDefaultSubobject<UParticleSystem>(TEXT("bombVFX"));
	//SetRootComponent(bombVFX);


}

// Called when the game starts or when spawned
void AbuildingBombVFX::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AbuildingBombVFX::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

