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

void AGun::Fire()
{
	// spawn particle effect
	UGameplayStatics::SpawnEmitterAttached(this->MuzzleFlash, this->Mesh, TEXT("MuzzleFlashSocket"));
	// get owner pawn
	APawn* ownerPawn = Cast<APawn>(GetOwner());
	if (ownerPawn == nullptr)
		return;
	AController* ownerController = ownerPawn->GetController();
	if (ownerController == nullptr)
		return;

	// get player viewpoint
	FVector playerViewPointLocation = FVector::ZeroVector;
	FRotator playerViewPointRotation = FRotator::ZeroRotator;
	ownerController->GetPlayerViewPoint(playerViewPointLocation, playerViewPointRotation);

	FVector LineEndPosition = playerViewPointLocation + playerViewPointRotation.Vector() * this->MaxRange;
	// Line trace
	FHitResult hit;
	FCollisionObjectQueryParams params;
	
	bool bSuccess = this->GetWorld()->LineTraceSingleByChannel(hit, playerViewPointLocation, LineEndPosition, ECollisionChannel::ECC_GameTraceChannel1);
	if (bSuccess)
	{
		FVector shotDirection = -playerViewPointRotation.Vector();
		UGameplayStatics::SpawnEmitterAtLocation(this->GetWorld(), this->ImpactEffect, hit.Location, shotDirection.Rotation());
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

