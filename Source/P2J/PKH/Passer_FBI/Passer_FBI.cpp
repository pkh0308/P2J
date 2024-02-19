// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Passer_FBI/Passer_FBI.h"
#include "PKH/Passer_FBI/PasserFBIAIController.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "PKH/Passer/PasserAIKey.h"
#include "PKH/Item/Item_IDCard.h"
#include "../../../../../../../Source/Runtime/LevelSequence/Public/LevelSequencePlayer.h"
#include "KIsmet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"
#include "JYJ/PlayerZeroCharacter.h"

APasser_FBI::APasser_FBI()
{
	PrimaryActorTick.bCanEverTick = true;

	AIControllerClass = APasserFBIAIController::StaticClass();
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	// Weapon Mesh
	WeaponMeshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("WeaponMeshComp"));
	WeaponMeshComp->SetupAttachment(GetMesh(), TEXT("PistolSocket"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> WeaponMeshRef(TEXT("/Script/Engine.StaticMesh'/Game/PKH/Mesh/Pistol/g18_not_rigged.g18_not_rigged'"));
	if (WeaponMeshRef.Object)
	{
		WeaponMeshComp->SetStaticMesh(WeaponMeshRef.Object);
		WeaponMeshComp->SetRelativeLocation(FVector(1.431f, -4.902f, 1.482f));
		WeaponMeshComp->SetRelativeRotation(FRotator(90.472f, -94.023f, 86.738f));
	}

	// Animation
	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimRef(TEXT("/Game/PKH/Animations/PasserFBI/ABP_FBIAnimInstance.ABP_FBIAnimInstance_C"));
	if (AnimRef.Class)
	{
		GetMesh()->SetAnimInstanceClass(AnimRef.Class);
	}

	static ConstructorHelpers::FObjectFinder<UAnimMontage> AttackMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserFBI/AM_FBIAttack.AM_FBIAttack'"));
	if (AttackMontageRef.Object)
	{
		AttackMontage = AttackMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DamagedMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserFBI/AM_FBIDamaged.AM_FBIDamaged'"));
	if (DamagedMontageRef.Object)
	{
		DamagedMontage = DamagedMontageRef.Object;
	}
	static ConstructorHelpers::FObjectFinder<UAnimMontage> DeathMontageRef(TEXT("/Script/Engine.AnimMontage'/Game/PKH/Animations/PasserFBI/AM_FBIDeath.AM_FBIDeath'"));
	if (DeathMontageRef.Object)
	{
		DeathMontage = DeathMontageRef.Object;
	}

	// ID Card
	static ConstructorHelpers::FClassFinder<AItem_IDCard> IDCardRef(TEXT("/Game/PKH/Blueprints/Item/BP_IDCard.BP_IDCard_C"));
	if (IDCardRef.Class)
	{
		IDCardFactory = IDCardRef.Class;
	}

	// Status
	Hp = 5;
	WalkSpeed = 150;
	RunSpeed = 350;
}

void APasser_FBI::BeginPlay()
{
	Super::BeginPlay();

	BBComp = GetBlackboard();
	WeaponMeshComp->SetVisibility(false);

	IDCard = GetWorld()->SpawnActor<AItem_IDCard>(IDCardFactory);
	IDCard->SetActive(false);

	FMovieSceneSequencePlaybackSettings MovieSetting;
	ALevelSequenceActor* OutActor;
	SequencePlayer = ULevelSequencePlayer::CreateLevelSequencePlayer(GetWorld(), Sequence_FBIOut, MovieSetting, OutActor);
}

void APasser_FBI::Tick(float DeltaTime)
{
	if (IsRage)
	{
		if (BBComp)
		{
			APawn* TargetPawn = Cast<APawn>(BBComp->GetValueAsObject(PASSER_KEY_TARGET));
			if (TargetPawn)
			{
				FVector LookVector = TargetPawn->GetActorLocation() - GetActorLocation();
				LookVector.Z = 0.0f;
				FRotator TargetRotation = FRotationMatrix::MakeFromX(LookVector).Rotator();
				SetActorRotation(FMath::RInterpTo(GetActorRotation(), TargetRotation, DeltaTime, 1000));
			}
		}
		return;
	}

	if (IsDead && false == IsDropped)
	{
		if (GetActorLocation().Y > -1400)
		{
			IsDropped = true;
			IDCard->SetActive(true);
			IDCard->SetActorLocationAndRotation(GetActorLocation() + GetActorForwardVector() * -20, FRotator( 40 , 0 , 50 ));
		}
	}
}

void APasser_FBI::OnDamaged(int32 InDamage, AActor* NewTarget)
{
	if (IsDead)
	{
		return;
	}
	IsDamagedDelay = true;

	Hp -= InDamage;
	if (Hp <= 0)
	{
		OnDie();
	}
	else
	{
		// Sound
		int SFXIndex = FMath::RandRange( 0 , SFX_Damaged.Num() - 1 );
		UGameplayStatics::PlaySound2D( GetWorld() , SFX_Damaged[SFXIndex] , 1.4f );

		if (IsRage)
		{
			return;
		}

		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		PlayMontage(DamagedMontage);

		if (BBComp)
		{
			BBComp->SetValueAsBool(PASSER_KEY_ISHITDELAY, true);
			BBComp->SetValueAsObject(PASSER_KEY_TARGET, NewTarget);
		}

		if (Hp <= 3)
		{
			IsRage = true;
			UGameplayStatics::PlaySound2D( GetWorld() , SFX_Rage );
		}
	}
}

void APasser_FBI::OnDamagedEnd()
{
	Super::OnDamagedEnd();

	WeaponMeshComp->SetVisibility(IsRage);
	IsDamagedDelay = false;
}

void APasser_FBI::OnDie()
{
	IsDead = true;
	IsRage = false;
	WeaponMeshComp->SetVisibility(false);
	GetCharacterMovement()->MaxWalkSpeed = FastRunSpeed;

	// Sound
	UGameplayStatics::PlaySound2D( GetWorld() , SFX_Run );

	AActor* TargetActor = Cast<AActor>(GetBlackboard()->GetValueAsObject(PASSER_KEY_TARGET));
	if (TargetActor)
	{
		FVector DestinationVec = GetActorLocation() - TargetActor->GetActorLocation();
		DestinationVec.Z = 0;
		DestinationVec.Normalize();
		GetBlackboard()->SetValueAsVector(PASSER_KEY_HOMELOCATION, FVector(-700, 4000, 98));
	}
	GetBlackboard()->SetValueAsObject(PASSER_KEY_TARGET, nullptr);

	// Destroy
	FTimerHandle DestroyHandle;
	GetWorldTimerManager().SetTimer(DestroyHandle, FTimerDelegate::CreateLambda(
		[this]() {
			Destroy();
		}
	), 14.0f, false);

	// Quest
	APKHGameMode* GameMode = Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()));
	if (nullptr == GameMode)
	{
		return;
	}

	if (GameMode->CheckCurQuest(EQuestType::Q1_FightWithMan))
	{
		GameMode->ClearCurQuest();

		FTimerHandle Handle;
		GetWorldTimerManager().SetTimer(Handle, FTimerDelegate::CreateLambda(
			[&]() {
				Cast<APKHGameMode>(UGameplayStatics::GetGameMode(GetWorld()))->SetQuestGuideText(TEXT("ID 카드를 획득하십시오."));
			}), 11.2f, false);
	}

	// Sequence
	if (SequencePlayer)
	{
		GameMode->SetHpBar( false );
		SequencePlayer->Play();

		FTimerHandle HpHandle;
		GetWorldTimerManager().SetTimer(HpHandle , FTimerDelegate::CreateLambda(
			[GameMode]() {
				GameMode->SetHpBar( true );
			}), 11.0f, false);
	}
}

void APasser_FBI::Shoot()
{
	ACharacter* Target = Cast<ACharacter>(GetBlackboard()->GetValueAsObject(PASSER_KEY_TARGET));
	if (nullptr == Target)
	{
		return;
	}

	// Sound
	UGameplayStatics::PlaySound2D( GetWorld() , SFX_Shoot );

	FHitResult HResult;
	FCollisionQueryParams Param;
	Param.AddIgnoredActor(this);
	
	const FVector StartVec = GetActorLocation() + PistolOffset;
	FVector RandVec = Target->GetActorRightVector() * FMath::RandRange(-ShootYOffset, ShootYOffset) + Target->GetActorUpVector() * FMath::RandRange(-ShootZOffset, ShootZOffset);
	const FVector EndVec = Target->GetActorLocation() + RandVec;

	bool IsHit = GetWorld()->LineTraceSingleByChannel(HResult, StartVec, EndVec, ECollisionChannel::ECC_Pawn, Param);
	if (IsHit)
	{
		APlayerZeroCharacter* PlayerCharacter = Cast<APlayerZeroCharacter>(HResult.GetActor());
		if (PlayerCharacter)
		{
			PlayerCharacter->TakePlayerDamaged(2);
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Blood, HResult.GetActor()->GetActorLocation() , FRotator(), FVector(0.6f) );
		}
	}
}
