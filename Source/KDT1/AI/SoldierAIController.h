// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIController.h"
#include "SoldierAIController.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API ASoldierAIController : public AAIController
{
	GENERATED_BODY()

public:
	ASoldierAIController();

protected:
	UBehaviorTree* mBehaviorTree;
	UBlackboardData* mBlackboard;
	
	virtual void OnPossess(APawn* InPawn) override;
	virtual void OnUnPossess() override;
};