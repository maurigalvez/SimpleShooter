// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"

void AShooterAIController::BeginPlay()
{
	Super::BeginPlay();
	this->PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(),0);
	// set focus on player pawn
	this->SetFocus(this->PlayerPawn, EAIFocusPriority::Gameplay);
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	// move actor
	this->MoveToActor(this->PlayerPawn, 200.0f);
}