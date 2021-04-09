// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	APawn* playerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(),0);
	// set focus on player pawn
	this->SetFocus(playerPawn, EAIFocusPriority::Gameplay);
}