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

	// Called every frame
	virtual void Tick(float DeltaTime) override;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;	

private:
	// Return whether gun hit something, and passes OUT hit and OUT shotDirection
	bool GunTrace(FHitResult& Hit, FVector& ShotDirection);

	// Return owner controller
	AController* GetOwnerController() const;

	// ------------
	// PROPERTIES
	// ------------
private:
	UPROPERTY(VisibleAnywhere)
	USceneComponent* Root = nullptr;

	UPROPERTY(VisibleAnywhere)
	USkeletalMeshComponent* Mesh = nullptr;

	UPROPERTY(EditAnywhere, Category = "General")
		float MaxRange = 1000.f;

	UPROPERTY(EditAnywhere, Category = "General")
		float Damage = 10.f;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* MuzzleFlash = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* MuzzleSound = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	UParticleSystem* ImpactEffect = nullptr;

	UPROPERTY(EditAnywhere, Category = "Effects")
	USoundBase* ImpactSound = nullptr;
};
