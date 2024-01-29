// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerOneCharacter.h"

// Sets default values
APlayerOneCharacter::APlayerOneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void APlayerOneCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerOneCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerOneCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void APlayerOneCharacter::Move()
{

}

void APlayerOneCharacter::OnAxisVertical(float value)
{

}

void APlayerOneCharacter::OnAxisHorizontal(float value)
{

}

void APlayerOneCharacter::OnActionJump()
{

}

void APlayerOneCharacter::OnAxisTurnYaw(float value)
{

}

void APlayerOneCharacter::OnAxisLookupPitch(float value)
{

}

