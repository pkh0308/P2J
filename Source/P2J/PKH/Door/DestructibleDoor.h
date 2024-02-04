// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PKH/Interface/DestructibleDoorInterface.h"
#include "DestructibleDoor.generated.h"

UCLASS()
class P2J_API ADestructibleDoor : public AActor, public IDestructibleDoorInterface
{
	GENERATED_BODY()
	
public:	
	ADestructibleDoor();

protected:
	virtual void BeginPlay() override;

// Component
protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UBoxComponent> BoxComp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<class UStaticMeshComponent> MeshComp;

// IDestructibleDoorInterface
public:
	void DestroyActor() override;
};
