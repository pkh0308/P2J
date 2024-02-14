// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerHPBar.h"
#include "PlayerZeroCharacter.h"
#include "../../../../../../../Source/Runtime/UMG/Public/Components/ProgressBar.h"

void UPlayerHPBar::NativeConstruct()
{
	Super::NativeConstruct();

	//나의 owner 를 가져와서 처리하고 싶다.
	player = GetOwningPlayer<APlayerZeroCharacter>();

	SetHP( 1 , 1 );
}

void UPlayerHPBar::NativeTick( const FGeometry& MyGeometry , float InDeltaTime )
{
	
}

void UPlayerHPBar::SetHP( int32 hp , int32 maxHP )
{
	HPBar->SetPercent( (float)hp / maxHP ); 
}
