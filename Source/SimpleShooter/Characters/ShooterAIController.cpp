// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	// check if there's a behaviour tree
	if (this->AIBehaviour != nullptr)
	{
		this->RunBehaviorTree(this->AIBehaviour);
	}

	/*this->PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(),0);
	// set focus on player pawn
	this->SetFocus(this->PlayerPawn, EAIFocusPriority::Gameplay);*/
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check if player is in sight
	/*if (this->LineOfSightTo(this->PlayerPawn))
	{
		// move actor
		this->MoveToActor(this->PlayerPawn, this->MaxDistanceFromTarget);
	}
	// player is not in sight
	else
	{
		this->ClearFocus(EAIFocusPriority::Gameplay);
		this->StopMovement();
	}	*/
}