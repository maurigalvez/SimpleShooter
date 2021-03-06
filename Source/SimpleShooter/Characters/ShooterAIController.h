// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "ShooterAIController.generated.h"

/**
 * Defines shooter player character
 */
UCLASS()
class SIMPLESHOOTER_API AShooterAIController : public AAIController
{
	GENERATED_BODY()
public:
	virtual void Tick(float DeltaTime) override;

	// check whether the controlled character is dead
	bool IsDead() const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere)
	class UBehaviorTree* AIBehaviour = nullptr;

	APawn* PlayerPawn = nullptr;
};
