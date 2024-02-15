// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/PlayerGameModeBase.h"
#include "PlayerHPBar.h"

void APlayerGameModeBase::BeginPlay()
{
	Super::BeginPlay();

	//healthUI = CreateWidget<UPlayerHPBar>( GetWorld() , playerHealthUIFactory );
	//healthUI->AddToViewport( 1 );

}
