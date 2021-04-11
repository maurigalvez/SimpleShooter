// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterAIController.h"
#include "Kismet/GameplayStatics.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

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

bool AShooterAIController::IsDead() const
{
	// check whether this character is dead
	AShooterCharacter* ShooterCharacter = Cast<AShooterCharacter>(this->GetPawn());
	if (ShooterCharacter != nullptr)
	{
		return ShooterCharacter->IsDead();
	}
	// if we don't have a pawn then yes, it's dead
	return true;
}

void AShooterAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);	
}