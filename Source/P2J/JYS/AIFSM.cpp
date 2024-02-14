// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/AIFSM.h"
#include "Enemy/EnemyAI.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Components/CapsuleComponent.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/GameFramework/Character.h"

// Sets default values for this component's properties
UAIFSM::UAIFSM()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIFSM::BeginPlay()
{
	Super::BeginPlay();

	// 내 본체를 기억하고싶다.
	me = Cast<AEnemyAI>( GetOwner() );
	
	
}


// Called every frame
void UAIFSM::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	switch (state)
	{
	case EAIState::IDLE:	TickIdle();			break;
	case EAIState::MOVE:	TickMove();			break;
	case EAIState::ATTACK:	TickAttack();		break;
	case EAIState::DAMAGE:	TickDamage();		break;
	case EAIState::DIE:		TickDie();			break;
	}
}

void UAIFSM::TickIdle()
{
	// 1. 주인공을 찾아서 목적지로 기억하고싶다.
	FVector targetdist = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - me->GetActorLocation();
	//target = UGameplayStatics::GetPlayerCharacter(GetWorld(), 0);
	// 2. 만약 목적지가 있다면
	if (targetdist.Length() < 450)
	{
		// 3. 이동상태로 전이하고싶다. -> state의 값을 MOVE로 바꾸고싶다.
		SetState(EAIState::MOVE);
	}
}

void UAIFSM::TickMove()
{
	// 0. 목적지를 향하는 방향을 구하고싶다.
	FVector dir = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - me->GetActorLocation();
	// 1. me가 그 방향으로 이동하게 하고싶다.
	me->AddMovementInput( dir.GetSafeNormal() );
	// 2. 목적지와의 거리를 기억하고싶다.
	float dist = (me->GetActorLocation() - GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation()).Size();
	// 3. 만약 목적지와의 거리가 attackDist보다 작다면
	if (dist < attackDist)
	{
		// 4. 공격상태로 전이하고싶다.
		SetState( EAIState::ATTACK );


		// FVector dir = target->GetActorLocation() - me->GetActorLocation();
		// me->AddMovementInput( dir.GetSafeNormal() );
	}
}

void UAIFSM::TickAttack()
{
	// 1. 시간이 흐르다가
	currentTime += GetWorld()->GetDeltaSeconds();
	/*UE_LOG( LogTemp , Warning , TEXT( "Attack TEST1 %f"), currentTime );*/
	if (currentTime > attackWaitTime)// 2. 현재 시간이 공격 대기시간을 초과하면
	{
		// 3. 현재시간을 초기화 하고 싶다.
		currentTime = 0;
		// 4. 목적지와의 거리를 재고 
		FVector distance = GetWorld()->GetFirstPlayerController()->GetPawn()->GetActorLocation() - me->GetActorLocation();
		float targetdist = distance.Length();

		if (targetdist > attackDist)// 5. 그 거리가 공격가능거리를 초과한다면
		{
			/*UE_LOG( LogTemp , Warning , TEXT( "Attack TEST2 %f" ) , currentTime );*/

			// 6.	이동상태로 전이하고싶다.
			SetState( EAIState::MOVE );
		}
		else// 7. 그렇지 않다면
		{
			// 8.공격을 하고싶다.
			UE_LOG( LogTemp , Warning , TEXT( "Enemy->Player Attack!!" ) );
			GEngine->AddOnScreenDebugMessage( -1 , 3 , FColor::Cyan , TEXT( "Enemy->Player Attack!!" ) );

		}
	}
}

void UAIFSM::TickDamage()
{

}

void UAIFSM::TickDie()
{
	if (false == isDieDone)
		return;

	//// 2초동안 아래로 이동하다가
	//float deltaTime = GetWorld()->GetDeltaSeconds();
	//FVector P0 = me->GetActorLocation();
	//FVector velocity = FVector::DownVector * 500;
	//me->SetActorLocation(P0 + velocity * GetWorld()->GetDeltaSeconds());

	//// 시간이 흐르다가
	//currentTime += deltaTime;
	//// 2초가 되면 
	//if (currentTime > 2)
	//{
	//	// 2초가 되면 스스로 파괴하고싶다
	//	me->Destroy();
	//}
	
	// 죽음 애니메이션 몽타주 재생
	UE_LOG(LogTemp,Warning, TEXT("test11111"));
	me->PlayAnimMontage( enemyMontage , 1 );
	isDieDone = false;

}

void UAIFSM::TakeDamage( int damage )
{
	// 체력을 damage만큼 줄이고 싶다
	me->hp -= damage;
	UE_LOG(LogTemp, Warning, TEXT("Enemy2 test1"));
	UE_LOG( LogTemp , Warning , TEXT( "Enemy2 hp %d" ), me->hp );

	if (me->hp < 0)
	{
		UE_LOG( LogTemp , Warning , TEXT( "Enemy2 test2" ) );
		me->hp = 0;
		// 체력이 0 이하라면 Die상태로 전이하고싶다
		SetState( EAIState::DIE );
	}

	me->PlayAnimMontage( enemyMontage , 1, TEXT("Die"));
	isDieDone = false;


	////충돌체를 끄고 싶다
	//me->GetCapsuleComponent()->SetCollisionEnabled( ECollisionEnabled::NoCollision );
}

void UAIFSM::SetState(EAIState next)
{
	state = next;
	//currentTime = 0;
}

