// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SimpleShooterGameModeBase.h"
#include "KillEmAllGameMode.generated.h"

/**
 * 
 */
UCLASS()
class SIMPLESHOOTER_API AKillEmAllGameMode : public ASimpleShooterGameModeBase
{
	GENERATED_BODY()

public:
    // fired when a pawn is killed
    void PawnKilled(APawn* PawnKilled) override;

private:
    // Handle End Game event
    void EndGame(bool bIsPlayerWinner);

};
