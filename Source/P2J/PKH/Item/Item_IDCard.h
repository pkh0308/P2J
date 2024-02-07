// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Item/ItemBase.h"
#include "Item_IDCard.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API AItem_IDCard : public AItemBase
{
	GENERATED_BODY()

public:
	AItem_IDCard();

protected:
	virtual void GetItem(class APlayerZeroCharacter* InCharacter) override;
	
};
