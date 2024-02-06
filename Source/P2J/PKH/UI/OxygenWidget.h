// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "OxygenWidget.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API UOxygenWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativeConstruct() override;
	
// Oxygen
protected:
	UFUNCTION()
	void UpdateTimer();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UProgressBar> OxygenGuage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta = (BindWidget))
	TObjectPtr<class UTextBlock> OxygenText;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32 MaxTime = 100;

	int32 CurTime = 0;

	FTimerHandle OxygenHandle;

public:
	void StartOxygenTimer();
	void StopOxygenTimer();

	FORCEINLINE	float GetOxygenRate() const { return (float)CurTime / MaxTime; }
};
