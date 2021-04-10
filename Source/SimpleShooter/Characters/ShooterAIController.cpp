// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();

	this->PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	// check if there's a behaviour tree
	if (this->AIBehaviour != nullptr)
	{
		this->RunBehaviorTree(this->AIBehaviour);

		// set start location
		this->GetBlackboardComponent()->SetValueAsVector(TEXT("StartLocation"), this->GetPawn()->GetActorLocation());

		// get blackboard component
		this->GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), this->PlayerPawn->GetActorLocation());
	}

	/*
	// set focus on player pawn
	this->SetFocus(this->PlayerPawn, EAIFocusPriority::Gameplay);*/
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// check if player is in sight
	if (this->LineOfSightTo(this->PlayerPawn))
	{
		// get blackboard component
		this->GetBlackboardComponent()->SetValueAsVector(TEXT("PlayerLocation"), this->PlayerPawn->GetActorLocation());
		// get blackboard component
		this->GetBlackboardComponent()->SetValueAsVector(TEXT("LastKnownPlayerLocation"), this->PlayerPawn->GetActorLocation());
	}
	// player is not in sight
	else
	{
		this->GetBlackboardComponent()->ClearValue(TEXT("PlayerLocation"));		
	}	
}