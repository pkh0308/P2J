// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PKH/Item/ItemBase.h"
#include "Item_Disk.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API AItem_Disk : public AItemBase
{
	GENERATED_BODY()

public:
	AItem_Disk();

protected:
	virtual void GetItem(class ACharacter* InCharacter) override;
	
};
