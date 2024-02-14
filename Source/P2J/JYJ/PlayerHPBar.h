// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "PlayerHPBar.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UPlayerHPBar : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct() override;
	virtual void NativeTick( const FGeometry& MyGeometry , float InDeltaTime ) override;

	UPROPERTY(EditDefaultsOnly, meta = (BindWidget))
	class UProgressBar* HPBar;

	void SetHP( int32 hp , int32 maxHP );

	UPROPERTY()
	class APlayerZeroCharacter* player;
	
};
