// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"

ASoldierAIController::ASoldierAIController()
{
	static ConstructorHelpers::FObjectFinder<UBehaviorTree> SoldierTree(TEXT("/Script/AIModule.BehaviorTree'/Game/Main/BT_Soldier.BT_Soldier'"));
	if (SoldierTree.Succeeded())
	{
		mBehaviorTree = SoldierTree.Object;
	}

	static ConstructorHelpers::FObjectFinder<UBlackboardData> SoldierData(TEXT("/Script/AIModule.BlackboardData'/Game/Main/BB_Soldier.BB_Soldier'"));
	if (SoldierData.Succeeded())
	{
		mBlackboard = SoldierData.Object;
	}
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
