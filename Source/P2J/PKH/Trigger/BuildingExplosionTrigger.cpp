// Fill out your copyright notice in the Description page of Project Settings.


#include "PKH/Trigger/BuildingExplosionTrigger.h"
#include "JYJ/PlayerZeroCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "PKH/Game/PKHGameMode.h"

void ABuildingExplosionTrigger::OnPlayerOverlap( UPrimitiveComponent* OverlappedComponent , AActor* OtherActor , UPrimitiveComponent* OtherComp , int32 OtherBodyIndex , bool bFromSweep , const FHitResult& SweepResult )
{
	Super::OnPlayerOverlap( OverlappedComponent , OtherActor , OtherComp , OtherBodyIndex , bFromSweep , SweepResult );

	if (false == OtherActor->IsA<APlayerZeroCharacter>())
	{
		return;
	}
	APKHGameMode* GameMode = Cast<APKHGameMode>( UGameplayStatics::GetGameMode(GetWorld()) );
	if (nullptr == GameMode)
	{
		return;
	}
	if (false == GameMode->CheckCurQuest( EQuestType::Q5_ExitBuilding ))
	{
		return;
	}

	GameMode->ClearCurQuest();
	PlaySequence();

	// Explosion
	FTimerHandle Handle1;
	GetWorldTimerManager().SetTimer( Handle1 , FTimerDelegate::CreateLambda(
		[this]() { 
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( 1510.65f, 14861.57f, 7307) , FRotator(0, -105, 0) , FVector( 4.0f ) );
		}), 2.0f, false);
	FTimerHandle Handle2;
	GetWorldTimerManager().SetTimer( Handle2 , FTimerDelegate::CreateLambda(
		[this]() { 
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( -1753.4f, 14963.35f, 7307) , FRotator(0, -65, 0) , FVector( 4.0f ) );
		} ) , 2.5f , false );

	FTimerHandle Handle3;
	GetWorldTimerManager().SetTimer( Handle3 , FTimerDelegate::CreateLambda(
		[this]() { 
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( -349.3f, 15388.96f, 6000) , FRotator(0, -85, 0) , FVector( 5.0f ) );
		} ) , 3.0f , false );

	FTimerHandle Handle4;
	GetWorldTimerManager().SetTimer( Handle4 , FTimerDelegate::CreateLambda(
		[this]() {
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( 2092.13f, 14705.76f, 6312) , FRotator(0, -105, 0) , FVector( 3.0f ) );
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Fire , FVector( 2092.13f , 14705.76f , 6312 ) , FRotator( 0 , -105 , 0 ) , FVector( 1.2f ) );
		} ) , 4.2f , false );
	FTimerHandle Handle5;
	GetWorldTimerManager().SetTimer( Handle5 , FTimerDelegate::CreateLambda(
		[this]() { 
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( 547.62f, 15119.61f, 6312) , FRotator(0, -105, 0) , FVector( 3.0f ) );
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Fire , FVector( 547.62f , 15119.61f , 6312 ) , FRotator( 0 , -105 , 0 ) , FVector( 1.2f ) );
		} ) , 5.2f , false );
	FTimerHandle Handle6;
	GetWorldTimerManager().SetTimer( Handle6 , FTimerDelegate::CreateLambda(
		[this]() {
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector(-1196.75f, 15637.93f, 6312) , FRotator(0, -70, 0) , FVector( 3.0f ) );
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Fire , FVector( -1196.75f , 15637.93f , 6312 ) , FRotator( 0 , -70 , 0 ) , FVector( 1.2f ) );
		} ) , 6.2f , false );
	FTimerHandle Handle7;
	GetWorldTimerManager().SetTimer( Handle7 , FTimerDelegate::CreateLambda(
		[this]() {
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Explosion , FVector( -2367.60f, 15211.78f, 6312 ) , FRotator(0, -70, 0) , FVector( 3.0f ) );
			UGameplayStatics::SpawnEmitterAtLocation( GetWorld() , VFX_Fire , FVector( -2367.60f , 15211.78f , 6312 ) , FRotator( 0 , -70 , 0 ) , FVector( 1.2f ) );
		} ) , 7.2f , false );

	// Open Level
	FTimerHandle Handle9;
	GetWorldTimerManager().SetTimer( Handle9 , FTimerDelegate::CreateLambda(
		[GameMode]() {
			GameMode->ShowFadeOut();
		} ) , 11.0f , false );

	FTimerHandle Handle10;
	GetWorldTimerManager().SetTimer( Handle10 , FTimerDelegate::CreateLambda(
		[GameMode]() {
			GameMode->OpenLevel(ELevelSelect::Level3);
		} ) , 14.0f , false );
}
