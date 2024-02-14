// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "PlayerGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APlayerGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	virtual void BeginPlay() override;


	UPROPERTY( EditAnywhere )
	TSubclassOf<class UUserWidget> playerHealthUIFactory;

	UPROPERTY()
	class UPlayerHPBar* healthUI;
	
};
