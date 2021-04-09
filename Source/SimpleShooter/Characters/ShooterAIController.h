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

protected:
	virtual void BeginPlay() override;

	APawn* PlayerPawn = nullptr;
};
