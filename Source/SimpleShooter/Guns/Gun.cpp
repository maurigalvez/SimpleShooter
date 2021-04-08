// Fill out your copyright notice in the Description page of Project Settings.


#include "Gun.h"
#include "Components/SkeletalMeshComponent.h"
#include "Kismet/GameplayStatics.h"

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

