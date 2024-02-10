// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "WetBroom.generated.h"

UCLASS()
class P2J_API AWetBroom : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AWetBroom();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	virtual void PostInitializeComponents() override;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	class UStaticMeshComponent* BroomstickComp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
    class UBoxComponent* Trigger;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCleanQEnabled;

	UPROPERTY()
	class APlayerTwoCharacter* player2;

	UFUNCTION()
	void OnCharacterOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnMudOverlap(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

private:
	bool nextQuest;


};
