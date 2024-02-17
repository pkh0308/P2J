// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "PlayerTwoCharacter.generated.h"

/**
 * 
 */
UCLASS()
class P2J_API APlayerTwoCharacter : public APlayerZeroCharacter
{
	GENERATED_BODY()
	
public:
	APlayerTwoCharacter();

	virtual void BeginPlay() override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	virtual void NotifyActorBeginOverlap(AActor* OtherActor) override;
	virtual void Tick( float DeltaTime ) override;

	UFUNCTION()
	void OnBombOverlap( UPrimitiveComponent* OverlappedComp , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult );

	void cleanStart();
	void cleanEnd();

	void setupDynamite();
	
	UPROPERTY()
	class AMudActor* mud;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bCleanQEnabled;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool bBombQEnabled;

	UPROPERTY(EditAnywhere)
	TSubclassOf<class ADynamite> dynamiteFactory;

	UPROPERTY(EditAnywhere)
	FTransform dynamiteTransform;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	bool questState;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 dynamiteCnt;

	int32 mudCnt = 0;

};
