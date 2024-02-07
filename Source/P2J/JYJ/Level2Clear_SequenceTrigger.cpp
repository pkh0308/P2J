// Fill out your copyright notice in the Description page of Project Settings.


#include "JYJ/Level2Clear_SequenceTrigger.h"
#include "PlayerTwoCharacter.h"
#include "../../../../../../../Source/Runtime/Engine/Classes/Kismet/GameplayStatics.h"
#include "../PKH/Game/PKHGameMode.h"

void ALevel2Clear_SequenceTrigger::OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	Super::OnPlayerOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );

	FTimerHandle Handle;
	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode( GetWorld() ) );


	if (OtherActor->IsA<APlayerTwoCharacter>())
	{
		UE_LOG(LogTemp,Warning, TEXT("TEST"));
		FVector spawnLoc1 = FVector( 1784.0 , 14683.0 , 4632.0 );
		FVector spawnLoc2 = FVector( 320.0 , 14999.0 , 4877.0 );
		FVector spawnLoc3 = FVector( 149.0 , 16789.0 , 4675.0 );
		FVector spawnLoc4 = FVector( 2708.0 , 15515.0 , 5241.0 );


		FRotator spawnRot = FRotator(0);
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld(),  bombVFX,  spawnLoc1 , spawnRot, FVector( 10 ) );
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , bombVFX , spawnLoc2 , spawnRot, FVector( 10 ) );
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , bombVFX , spawnLoc3 , spawnRot, FVector( 10 ) );
		UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , bombVFX , spawnLoc4 , spawnRot, FVector( 10 ) );
		//UGameplayStatics::SpawnEmitterAtLocation()

	}

}	
