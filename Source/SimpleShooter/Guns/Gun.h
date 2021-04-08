// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Gun.generated.h"

UCLASS()
class SIMPLESHOOTER_API AGun : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AGun();

	// Fire this weapon
	void Fire();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere)
	UParticleSystem* ImpactEffect = nullptr;

	UPROPERTY(EditAnywhere)
	float MaxRange = 1000.f;
};
