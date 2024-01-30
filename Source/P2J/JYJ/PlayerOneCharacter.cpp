// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerOneCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"

// Sets default values
APlayerOneCharacter::APlayerOneCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 70, 90));

	p1camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("p1camComp"));
	p1camComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/PKH/Mesh/PasserA/Ch06_nonPBR.Ch06_nonPBR'"));

	if (tmpMesh.Succeeded()) {
		//GetMesh()->set
	}

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

