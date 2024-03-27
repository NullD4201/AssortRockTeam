// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"

ASoldierAIController::ASoldierAIController()
{
}

void ASoldierAIController::OnPossess(APawn* InPawn)
{
	Super::OnPossess(InPawn);

	if (mBlackboard)
	{
		UBlackboardComponent* BlackboardRef = Blackboard;

		if (UseBlackboard(mBlackboard, BlackboardRef))
		{
			RunBehaviorTree(mBehaviorTree);
		}
	}
}

void ASoldierAIController::OnUnPossess()
{
	Super::OnUnPossess();
}
