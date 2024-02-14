// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "SequenceTrigger.generated.h"

UCLASS()
class P2J_API ASequenceTrigger : public AActor
{
	GENERATED_BODY()
	
public:	
	ASequenceTrigger();

protected:
	virtual void BeginPlay() override;

	virtual void OnSequenceFinished();

// Component
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY()
	TObjectPtr<class ULevelSequencePlayer> SequencePlayer;

	UFUNCTION()
	virtual void OnPlayerOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

// Sequence 
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class ULevelSequence> SequenceFactory;

public:
	void PlaySequence();

	FORCEINLINE ASequenceTrigger* GetTrigger() { return this; }
};
