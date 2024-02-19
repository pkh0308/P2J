// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Actor.h"
#include "../JYJ/PlayerThirdCharacter.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// sphereComp를 루트로
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	movementComp->SetUpdatedComponent(sphereComp);

	// speed 설정, 바운드 설정
	movementComp->InitialSpeed = 1000.f;
	movementComp->MaxSpeed = 1000.f;
	movementComp->bShouldBounce = true;
	movementComp->ProjectileGravityScale = 0;

	sphereComp->SetCollisionProfileName(TEXT("Bullet"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// 메시의 크기를 0.25로 하고 싶다
	meshComp->SetWorldScale3D(FVector(0.25f));
	//충돌체의 반지름을 12.5 하고싶다
	sphereComp->SetSphereRadius(0.05f);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	movementComp->Velocity = GetActorForwardVector() * movementComp->MaxSpeed;
	// UE_LOG( LogTemp , Log , TEXT( "dasdasds" ) );

	// 총알 액터의 수명을 5초로 하고 싶다. 타이머를 이용해서 처리하고 싶다.
	// FTimerHandle timerHandle;
	//GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 10, false);
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	//SetActorLocation( this->GetActorForwardVector() * 3000 * GetWorld()->DeltaTimeSeconds);
}

void ABulletActor::NotifyActorBeginOverlap( AActor* OtherActor )
{
	APlayerThirdCharacter* player = Cast<APlayerThirdCharacter>(OtherActor);
	if (player)
	{
		player->TakePlayerDamaged(1);
	}
}

