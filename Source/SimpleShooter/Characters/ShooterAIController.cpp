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
	}
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}