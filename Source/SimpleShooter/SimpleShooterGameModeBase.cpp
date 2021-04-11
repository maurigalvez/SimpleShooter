// Copyright Epic Games, Inc. All Rights Reserved.


#include "SimpleShooterGameModeBase.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "SimpleShooter/Actors/SpawnPoint.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

void ASimpleShooterGameModeBase::BeginPlay()
{
	Super::BeginPlay();
	// handle start game
	this->GameStart();
}

void ASimpleShooterGameModeBase::PawnKilled(APawn* PawnKilled)
{

}

void ASimpleShooterGameModeBase::SpawnEnemies()
{
	TArray<AActor*> SpawnPoints;
	UGameplayStatics::GetAllActorsOfClass(this->GetWorld(), ASpawnPoint::StaticClass(), SpawnPoints);

	// iterate through spawnPoints to spawn turrets
	for (AActor* spawnPoint : SpawnPoints)
	{
		// spawn actor
		GetWorld()->SpawnActor<AShooterCharacter>(this->EnemyToSpawn, spawnPoint->GetActorLocation(), spawnPoint->GetActorRotation());
	}
}

void ASimpleShooterGameModeBase::GameStart()
{
	// spawn enemies
	this->SpawnEnemies();
}