// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAIController.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Sight.h"
#include "Perception/AISense.h"
#include "../Character/MainCharacter.h"


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

	SetupPerceptionSystem();
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

void ASoldierAIController::SetupPerceptionSystem()
{
	SightConfig = CreateDefaultSubobject<UAISenseConfig_Sight>(TEXT("Sight Config"));
	PerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("AIPerception Component"));

	SightConfig->SightRadius = 1000.f;
	SightConfig->LoseSightRadius = SightConfig->SightRadius + 200.f;
	SightConfig->PeripheralVisionAngleDegrees = 60.f;
	SightConfig->SetMaxAge(5.f);
	SightConfig->AutoSuccessRangeFromLastSeenLocation = 520.f;
	SightConfig->DetectionByAffiliation.bDetectEnemies = true;
	SightConfig->DetectionByAffiliation.bDetectFriendlies = true;
	SightConfig->DetectionByAffiliation.bDetectNeutrals = true;

	PerceptionComponent->ConfigureSense(*SightConfig);
	PerceptionComponent->SetDominantSense(SightConfig->GetSenseImplementation());
	PerceptionComponent->OnTargetPerceptionUpdated.AddDynamic(this, &ASoldierAIController::OnTargetDetected);

}

void ASoldierAIController::OnTargetDetected(AActor* Actor, FAIStimulus const Stimulus)
{
	if (auto* const AICharacter = Cast<AMainCharacter>(Actor))
	{
		GetBlackboardComponent()->SetValueAsBool(TEXT("CanSeePlayer"), Stimulus.WasSuccessfullySensed());

		if (!(GetBlackboardComponent()->GetValueAsBool(TEXT("IsInRadius"))))
		{
			GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), AICharacter);
		}
	}
}