// Fill out your copyright notice in the Description page of Project Settings.


#include "JYS/AIAnim.h"
#include "Enemy/EnemyAI.h"



void UAIAnim::NativeInitializeAnimation()
{
	auto owner = TryGetPawnOwner();
	if (nullptr == owner)
		return;
	AEnemyAI* me = Cast<AEnemyAI>( owner );

	aiFSM = me->aiFSM;
}

void UAIAnim::NativeUpdateAnimation( float DeltaSeconds )
{
	if (nullptr == aiFSM)
		return;

	state = aiFSM->state;
}

void UAIAnim::AnimNotify_DieEnd()
{
	aiFSM->SetState( EAIState::MOVE );
}
