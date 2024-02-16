// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AutoCar.generated.h"

UCLASS()
class P2J_API AAutoCar : public AActor
{
	GENERATED_BODY()
	
public:	
	AAutoCar();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;

// Component
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> MeshComp;

// Move 
protected:
	float MoveSpeed = 500.0f;
	float RotationSpeed = 10.0f;

};
