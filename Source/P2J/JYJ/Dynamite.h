// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Dynamite.generated.h"

UCLASS()
class P2J_API ADynamite : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADynamite();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* DynamiteBomb1;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* DynamiteBomb2;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* DynamiteBomb3;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* DynamiteBomb4;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class UBoxComponent* Trigger;

};
