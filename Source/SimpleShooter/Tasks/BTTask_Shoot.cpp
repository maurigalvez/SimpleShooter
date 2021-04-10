// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Shoot.h"
#include "AIController.h"
#include "SimpleShooter/Characters/ShooterCharacter.h"

UBTTask_Shoot::UBTTask_Shoot()
{
	this->NodeName = TEXT("Shoot");
}

EBTNodeResult::Type UBTTask_Shoot::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);
	//get AI controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return EBTNodeResult::Failed;
	}	
	AShooterCharacter* shooter = Cast<AShooterCharacter>(AIController->GetPawn()); // cast will return if GetPawn() is nullptr
	if (shooter == nullptr)
	{
		return EBTNodeResult::Failed;
	}
	shooter->FireWeapon();
	return EBTNodeResult::Succeeded;
}
