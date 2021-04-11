// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterPlayerController.h"
#include "TimerManager.h"
#include "Blueprint/UserWidget.h"

void AShooterPlayerController::BeginPlay()
{
	// create HUD screen instance
	this->HudScreenInstance = CreateWidget(this, this->HudScreen);
	if (this->HudScreenInstance != nullptr)
	{
		this->HudScreenInstance->AddToViewport();
	}
}

void AShooterPlayerController::GameHasEnded(class AActor* EndGameFocus, bool bIsWinner)
{
	Super::GameHasEnded(EndGameFocus, bIsWinner);
	// destroy hud Screen instance
	if (this->HudScreenInstance != nullptr)
	{
		this->HudScreenInstance->RemoveFromViewport();
	}
	// winner screen
	if (bIsWinner)
	{
		// create win screen instance
		UUserWidget* WinScreenInstance = CreateWidget(this, this->WinScreen);
		if (WinScreenInstance != nullptr)
		{
			WinScreenInstance->AddToViewport();
		}
	}
	else
	{
		// create lose screen instance
		UUserWidget* LoseScreenInstance = CreateWidget(this, this->LoseScreen);
		if (LoseScreenInstance != nullptr)
		{
			LoseScreenInstance->AddToViewport();
		}
	}

	this->GetWorldTimerManager().SetTimer(this->RestartTimer, this, &APlayerController::RestartLevel, this->RestartDelay);
}