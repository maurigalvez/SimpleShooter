// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "SimpleShooterGameModeBase.generated.h"

/**
 * Handle shooter character mode
 */
UCLASS()
class SIMPLESHOOTER_API ASimpleShooterGameModeBase : public AGameModeBase
{
	GENERATED_BODY()

public:
	// fired when a pawn is killed
	virtual void PawnKilled(APawn* PawnKilled);

protected:
	virtual void BeginPlay() override;

	// Spawn enemies in level
	void SpawnEnemies();
	// Fired when game is started
	void GameStart();

	UPROPERTY(EditDefaultsOnly, Category = "Game Settings")
	TSubclassOf<class AShooterCharacter> EnemyToSpawn;
};
