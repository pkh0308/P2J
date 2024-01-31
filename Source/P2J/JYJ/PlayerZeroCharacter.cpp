// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"

// Sets default values
APlayerZeroCharacter::APlayerZeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(RootComponent);
	springArmComp->SetWorldLocation(FVector(0, 70, 90));

	p1camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("p1camComp"));
	p1camComp->SetupAttachment(springArmComp);

	//punchComp = CreateDefaultSubobject<USphereComponent>(TEXT("punchComp"));
	//punchComp->SetupAttachment(GetMesh());

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/JYJ/Mesh/Player1/Ch06_nonPBR.Ch06_nonPBR'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> ABP_Player(TEXT("/Script/Engine.AnimBlueprint'/Game/JYJ/Animations/ABP_Player.ABP_Player'"));
	if (ABP_Player.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP_Player.Class);
	}

	bUseControllerRotationYaw = true;
	springArmComp->bUsePawnControlRotation = true;
	GetCharacterMovement()->bOrientRotationToMovement = false;

}

// Called when the game starts or when spawned
void APlayerZeroCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerZeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	Move();

}

// Called to bind functionality to input
void APlayerZeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &APlayerZeroCharacter::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &APlayerZeroCharacter::OnAxisVertical);
	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerZeroCharacter::OnActionJump);
	PlayerInputComponent->BindAction(TEXT("Punch"), IE_Pressed, this, &APlayerZeroCharacter::Attack);

	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &APlayerZeroCharacter::OnAxisTurnYaw);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APlayerZeroCharacter::OnAxisLookupPitch);



}

void APlayerZeroCharacter::Move()
{
	FTransform trans = p1camComp->GetComponentTransform();
	AddMovementInput(trans.TransformVector(direction));


}

void APlayerZeroCharacter::OnAxisVertical(float value)
{
	direction.X = value;
}

void APlayerZeroCharacter::OnAxisHorizontal(float value)
{
	direction.Y = value;
}

void APlayerZeroCharacter::OnActionJump()
{
	Jump();
}



void APlayerZeroCharacter::OnAxisTurnYaw(float value)
{
	AddControllerYawInput(value);
}

void APlayerZeroCharacter::OnAxisLookupPitch(float value)
{
	AddControllerPitchInput(value);
}

void APlayerZeroCharacter::Attack()
{
	auto AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	if (nullptr == AnimInstance) return;

	AnimInstance->PlayerAttackMontage();
}

