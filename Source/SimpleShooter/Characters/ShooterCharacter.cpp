// Fill out your copyright notice in the Description page of Project Settings.


#include "ShooterCharacter.h"
#include "SimpleShooter/Guns/Gun.h"
#include "Components/CapsuleComponent.h"
#include "SimpleShooter/SimpleShooterGameModeBase.h"

// Sets default values
AShooterCharacter::AShooterCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AShooterCharacter::BeginPlay()
{
	Super::BeginPlay();
	// spawn gun
	this->EquippedGun = this->GetWorld()->SpawnActor<AGun>(this->GunBlueprint);

	// hide weapon bone
	this->GetMesh()->HideBoneByName(TEXT("weapon_r"), EPhysBodyOp::PBO_None);

	// attach new gun
	this->EquippedGun->AttachToComponent(this->GetMesh(), FAttachmentTransformRules::KeepRelativeTransform, TEXT("WeaponSocket"));
	this->EquippedGun->SetOwner(this);

	// init health
	this->Health = this->MaxHealth;
}

// Called every frame
void AShooterCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AShooterCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	// bind movement axis
	PlayerInputComponent->BindAxis(TEXT("Forward"),this, &AShooterCharacter::MoveForward);
	PlayerInputComponent->BindAxis(TEXT("Right"), this, &AShooterCharacter::MoveRight);
	// bind look rotation axis
	PlayerInputComponent->BindAxis(TEXT("MouseY"),this, &APawn::AddControllerPitchInput);
	PlayerInputComponent->BindAxis(TEXT("MouseX"), this, &APawn::AddControllerYawInput);
	// bind controller rotation axis
	PlayerInputComponent->BindAxis(TEXT("LookUpRate"), this, &AShooterCharacter::LookUpRate);
	PlayerInputComponent->BindAxis(TEXT("LookRightRate"), this, &AShooterCharacter::LookRightRate);
	// bind actions
	PlayerInputComponent->BindAction(TEXT("Jump"), EInputEvent::IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction(TEXT("Fire"), EInputEvent::IE_Pressed, this, &AShooterCharacter::FireWeapon);
}

float AShooterCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	float damageTaken = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
	// clamp damage
	damageTaken = FMath::Min(Health, damageTaken);
	this->Health -= damageTaken;
	
	// check if player is dead
	if (this->IsDead())
	{
		// get hold of game mode and fire pawnkilled
		ASimpleShooterGameModeBase* GameMode = this->GetWorld()->GetAuthGameMode<ASimpleShooterGameModeBase>();
		if (GameMode != nullptr)
		{
			GameMode->PawnKilled(this);
		}
		this->DetachFromControllerPendingDestroy();
		this->GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);	
	}

	return damageTaken;
}

bool AShooterCharacter::IsDead() const
{
	return this->Health <= 0;
}

void AShooterCharacter::MoveForward(float AxisValue)
{
	this->AddMovementInput(this->GetActorForwardVector() * AxisValue);
}

void AShooterCharacter::MoveRight(float AxisValue)
{
	this->AddMovementInput(this->GetActorRightVector() * AxisValue);
}

void AShooterCharacter::LookUpRate(float AxisValue)
{
	this->AddControllerPitchInput(AxisValue * this->YRotationRate * this->GetWorld()->DeltaTimeSeconds);
}

void AShooterCharacter::LookRightRate(float AxisValue)
{
	this->AddControllerYawInput(AxisValue * this->XRotationRate * this->GetWorld()->GetDeltaSeconds());
}

void AShooterCharacter::FireWeapon()
{
	this->EquippedGun->Fire();
}

/*void AShooterCharacter::LookUp(float AxisValue)
{
	this->AddControllerPitchInput(AxisValue);
}*/

