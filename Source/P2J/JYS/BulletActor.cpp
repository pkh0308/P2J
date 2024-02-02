// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/BulletActor.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/SphereComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/StaticMeshComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/ProjectileMovementComponent.h"

// Sets default values
ABulletActor::ABulletActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// sphereComp�� ��Ʈ��
	sphereComp = CreateDefaultSubobject<USphereComponent>(TEXT("sphereComp"));
	SetRootComponent(sphereComp);
	meshComp = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("meshComp"));
	meshComp->SetupAttachment(RootComponent);

	movementComp = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("movementComp"));
	movementComp->SetUpdatedComponent(sphereComp);

	// speed ����, �ٿ�� ����
	movementComp->InitialSpeed = 3000.f;
	movementComp->MaxSpeed = 2000.f;
	movementComp->bShouldBounce = false;
	movementComp->ProjectileGravityScale = 0;

	sphereComp->SetCollisionProfileName(TEXT("BlockAll"));
	meshComp->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	// �޽��� ũ�⸦ 0.25�� �ϰ� �ʹ�
	meshComp->SetWorldScale3D(FVector(0.25f));
	//�浹ü�� �������� 12.5 �ϰ�ʹ�
	sphereComp->SetSphereRadius(12.5f);

}

// Called when the game starts or when spawned
void ABulletActor::BeginPlay()
{
	Super::BeginPlay();

	// �Ѿ� ������ ������ 5�ʷ� �ϰ� �ʹ�. Ÿ�̸Ӹ� �̿��ؼ� ó���ϰ� �ʹ�.
	FTimerHandle timerHandle;
	GetWorld()->GetTimerManager().SetTimer(timerHandle, FTimerDelegate::CreateLambda([this]()->void {this->Destroy(); }), 5, false);
	
}

// Called every frame
void ABulletActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

