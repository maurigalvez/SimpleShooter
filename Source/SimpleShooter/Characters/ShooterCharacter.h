// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "ShooterCharacter.generated.h"

class AGun;

UCLASS()
class SIMPLESHOOTER_API AShooterCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AShooterCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	// Used to process vertical movement of character
	void MoveForward(float AxisValue);

	// Used to process horizontal movement of character
	void MoveRight(float AxisValue);

	void LookUpRate(float AxisValue);

	void LookRightRate(float AxisValue);

	// used to fire equipped weapon
	void FireWeapon();

	// void LookUp(float AxisValue); - Not necessary because we are using AddControllerPitchInput

	UPROPERTY(EditAnywhere)
	float XRotationRate = 10.f;

	UPROPERTY(EditAnywhere)
	float YRotationRate = 10.f;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AGun> GunBlueprint;

	UPROPERTY()
	AGun* EquippedGun = nullptr;
};