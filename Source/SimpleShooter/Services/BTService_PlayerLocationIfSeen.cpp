// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_PlayerLocationIfSeen.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "GameFramework/Pawn.h"
#include "Kismet/GameplayStatics.h"
#include "AIController.h"

UBTService_PlayerLocationIfSeen::UBTService_PlayerLocationIfSeen()
{
	this->NodeName = TEXT("Update Player Location If Seen");
}

void UBTService_PlayerLocationIfSeen::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	// get player component

	APawn* PlayerPawn = UGameplayStatics::GetPlayerPawn(this->GetWorld(), 0);
	if (PlayerPawn == nullptr)
	{
		return;
	}
	//get AI controller
	AAIController* AIController = OwnerComp.GetAIOwner();
	if (AIController == nullptr)
	{
		return;
	}
	// get reference to blackboard component
	UBlackboardComponent* blackBoardComponent = OwnerComp.GetBlackboardComponent();
	// check if player is in sight
	if (AIController->LineOfSightTo(PlayerPawn))
	{
		// get blackboard component
		blackBoardComponent->SetValueAsObject(this->GetSelectedBlackboardKey(), PlayerPawn);	
	}
	// player is not in sight
	else
	{
		blackBoardComponent->ClearValue(this->GetSelectedBlackboardKey());
	}
}
