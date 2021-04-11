// Fill out your copyright notice in the Description page of Project Settings.


#include "KillEmAllGameMode.h"
#include "EngineUtils.h"
#include "GameFramework/Controller.h"
#include "SimpleShooter/Characters/ShooterAIController.h"

void AKillEmAllGameMode::PawnKilled(APawn* PawnKilled)
{
	Super::PawnKilled(PawnKilled);
	APlayerController* PlayerController = Cast<APlayerController>(PawnKilled->GetController());
	if (PlayerController != nullptr)
	{
		// fire game has ended
		this->EndGame(false);
		return;
	}	
	
	// check if AI is dead
	for (AShooterAIController* AIController : TActorRange<AShooterAIController>(this->GetWorld()))
	{
		// if at least one of the AI is not dead, player has not won yet
		if (!AIController->IsDead())
		{
			return;
		}
	}	
	this->EndGame(true);
}

void AKillEmAllGameMode::EndGame(bool bIsPlayerWinner)
{
	/// iterate through all controllers in the world
	// we do this to make sure that either player or AI can be set as the winner
	for (AController* Controller : TActorRange<AController>(this->GetWorld()))
	{
		// check whether it's player controller which is equal to whether player is the winner
		bool bIsWinner = Controller->IsPlayerController() == bIsPlayerWinner;
		Controller->GameHasEnded(Controller->GetPawn(), bIsWinner);
	}
}
