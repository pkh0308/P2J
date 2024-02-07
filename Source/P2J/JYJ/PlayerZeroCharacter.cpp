// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/SpringArmComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Camera/CameraComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMesh.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/CharacterMovementComponent.h"
#include "PlayerAnimInstance.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/KismetMathLibrary.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Engine/SkeletalMeshSocket.h"
#include "WeaponActor.h"
#include "../PKH/Passer/PasserBase.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../PKH/Game/PKHGameMode.h"

// Sets default values
APlayerZeroCharacter::APlayerZeroCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	springArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("springArmComp"));
	springArmComp->SetupAttachment(GetCapsuleComponent());
	springArmComp->SetWorldLocation(FVector(0, 0, 90));

	p1camComp = CreateDefaultSubobject<UCameraComponent>(TEXT("p1camComp"));
	p1camComp->SetupAttachment(springArmComp);

	ConstructorHelpers::FObjectFinder<USkeletalMesh> tmpMesh(TEXT("/Script/Engine.SkeletalMesh'/Game/JYJ/Mesh/Player1/Ch06_nonPBR.Ch06_nonPBR'"));
	if (tmpMesh.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(tmpMesh.Object);
		GetMesh()->SetRelativeLocationAndRotation(FVector(0, 0, -90), FRotator(0, -90, 0));

	}


	FName FirstAttackSocket(TEXT("FirstAttack"));
	if (GetMesh()->DoesSocketExist(FirstAttackSocket))
	{
		punchComp = CreateDefaultSubobject<USphereComponent>(TEXT("punchComp"));
		punchComp->SetupAttachment(GetMesh(), FirstAttackSocket);
		punchComp->SetRelativeScale3D(FVector(0.25f));
	}

	/*
	static ConstructorHelpers::FClassFinder<UPlayerAnimInstance> ABP_Player(TEXT("/Script/Engine.AnimBlueprint'/Game/JYJ/Animations/Player1/ABP_Player1.ABP_Player1'"));
	if (ABP_Player.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(ABP_Player.Class);
	}
	*/
	

	springArmComp->bUsePawnControlRotation = true;
	//springArmComp->SetRelativeRotation(FRotator::ZeroRotator);
	springArmComp->bInheritPitch = true;
	springArmComp->bInheritRoll = true;
	springArmComp->bInheritYaw = true;
	bUseControllerRotationYaw = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->RotationRate = FRotator(0.f, 720.f, 0.f);


	//충돌체 설정
	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));
	GetMesh()->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	SprintSpeedMultiplier = 2.0f;	//달리기 배속
	this->GetCharacterMovement()->MaxWalkSpeed = 600;
	this->GetCharacterMovement()->JumpZVelocity = 500.0f;


}

// Called when the game starts or when spawned
void APlayerZeroCharacter::BeginPlay()
{
	Super::BeginPlay();

	this->playerHP = this->playerMaxHP;

	PlayerAnim = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	check(PlayerAnim);
	//PlayerAnim->OnMontageEnded.AddDynamic(this, &APlayerZeroCharacter::OnPunchingMontageEnded);
	
	//GameOver 띄우기 위해 게임모드 선언
	gamemode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));

	punchComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	
}

// Called every frame
void APlayerZeroCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//Move();
	if (this->playerHP == 0)
	{
		PlayerAnim->PlayerDeathMontage();
		gamemode->GameOver(TEXT("당신은 시민에게 맞아 죽었습니다."));
	}

}

// Called to bind functionality to input
void APlayerZeroCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	PlayerInputComponent->BindAxis(TEXT("Move Right / Left"), this, &APlayerZeroCharacter::OnAxisHorizontal);
	PlayerInputComponent->BindAxis(TEXT("Move Forward / Backward"), this, &APlayerZeroCharacter::OnAxisVertical);
	PlayerInputComponent->BindAxis(TEXT("Turn Right / Left Mouse"), this, &APlayerZeroCharacter::OnAxisTurnYaw);
	PlayerInputComponent->BindAxis(TEXT("Look Up / Down Mouse"), this, &APlayerZeroCharacter::OnAxisLookupPitch);

	PlayerInputComponent->BindAction(TEXT("Jump"), IE_Pressed, this, &APlayerZeroCharacter::OnActionJump);
	PlayerInputComponent->BindAction(TEXT("Punch"), IE_Pressed, this, &APlayerZeroCharacter::Attack);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Pressed, this, &APlayerZeroCharacter::Sprint);
	PlayerInputComponent->BindAction(TEXT("Sprint"), IE_Released, this, &APlayerZeroCharacter::StopSprinting);


}

void APlayerZeroCharacter::PostInitializeComponents()
{
	Super::PostInitializeComponents();	
	punchComp->OnComponentBeginOverlap.AddDynamic(this, &APlayerZeroCharacter::OnEnemyOverlap);
}

void APlayerZeroCharacter::OnAxisVertical(float value)
{
	//direction.X = value;
	FVector Direction = UKismetMathLibrary::GetForwardVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, value);
}

void APlayerZeroCharacter::OnAxisHorizontal(float value)
{
	//direction.Y = value;
	FVector Direction = UKismetMathLibrary::GetRightVector(FRotator(0.0f, GetControlRotation().Yaw, 0.0f));
	AddMovementInput(Direction, value);

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

void APlayerZeroCharacter::OnEnemyOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	APasserBase* enemy = Cast<APasserBase>(OtherActor);

	if (enemy)
	{
		enemy->OnDamaged(1, this);
	}
}

void APlayerZeroCharacter::Attack()
{
	//auto AnimInstance = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
	//punchComp->SetCollisionProfileName(TEXT("PlayerAttack"));
	if (nullptr == PlayerAnim) return;
	PlayerAnim->PlayerAttackMontage();

}

void APlayerZeroCharacter::Sprint()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerZeroCharacter::StopSprinting()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

void APlayerZeroCharacter::TakePlayerDamaged(int damage)
{
	UE_LOG(LogTemp, Warning, TEXT("Player Hit TEST"));
	this->playerHP = this->playerHP - damage;

	PlayerAnim->PlayerHitMontage();

	if (this->playerHP < damage)
	{
		this->playerHP = 0;
	}
}

