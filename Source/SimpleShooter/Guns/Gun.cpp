// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "DrawDebugHelpers.h"

// Sets default values
AGun::AGun()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	// create root scene component
	this->Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	this->RootComponent = this->Root;
	// create mesh component
	this->Mesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	this->Mesh->SetupAttachment(this->Root);
}

AController* AGun::GetOwnerController() const
{
	// get and validate owner pawn
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr)
		return nullptr;

	return ownerPawn->GetController();
}

bool AGun::GunTrace(FHitResult& Hit, FVector& ShotDirection)
{
	// get and validate player controller
	AController* ownerController = this->GetOwnerController();
	if (ownerController == nullptr)
	{
		return false;
	}
	// get player viewpoint
	FVector playerViewPointLocation = FVector::ZeroVector;
	FRotator playerViewPointRotation = FRotator::ZeroRotator;
	ownerController->GetPlayerViewPoint(playerViewPointLocation, playerViewPointRotation);

	FVector LineEndPosition = playerViewPointLocation + playerViewPointRotation.Vector() * this->MaxRange;
	// Line trace

	FCollisionQueryParams params;
	params.AddIgnoredActor(this);
	params.AddIgnoredActor(this->GetOwner());

	ShotDirection = -playerViewPointRotation.Vector();
	return this->GetWorld()->LineTraceSingleByChannel(Hit, playerViewPointLocation, LineEndPosition, ECollisionChannel::ECC_GameTraceChannel1, params);
}

void AGun::Fire()
{
	// spawn MF particle effect and sound
	UGameplayStatics::SpawnEmitterAttached(this->MuzzleFlash, this->Mesh, TEXT("MuzzleFlashSocket"));
	UGameplayStatics::SpawnSoundAttached(this->MuzzleSound, this->Mesh, TEXT("MuzzleFlashSocket"));
	FHitResult hit;
	FVector shotDirection;
	bool bSuccess = GunTrace(hit, shotDirection);
	if (bSuccess)
	{		
		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), this->ImpactEffect, hit.Location, shotDirection.Rotation());
		UGameplayStatics::SpawnSoundAtLocation(this->GetWorld(), this->ImpactSound, hit.Location, shotDirection.Rotation());
		// damage actor
		if (hit.GetActor() != nullptr)
		{
			// get and validate owner controller
			AController* ownerController = this->GetOwnerController();
			if (ownerController == nullptr)
			{
				return;
			}
			// create dmaage event
			FPointDamageEvent damageEvent(this->Damage, hit, shotDirection, nullptr);
			hit.GetActor()->TakeDamage(this->Damage, damageEvent, ownerController, this);
		}
	}
}

// Called when the game starts or when spawned
void AGun::BeginPlay()
{
	Super::BeginPlay();	
}

// Called every frame
void AGun::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

