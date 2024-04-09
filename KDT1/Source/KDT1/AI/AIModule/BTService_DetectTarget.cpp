// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"

#include "AIController.h"
#include "../AIPawn.h"
#include "../AIState.h"
#include "KDT1/AI/AISoldier.h"
#include "KDT1/AI/SoldierAIController.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	ASoldierAIController* Controller = Cast<ASoldierAIController>(OwnerComp.GetAIOwner());
	if (!IsValid(Controller))
	{
		return;
	}
	AAISoldier*		Soldier = Cast<AAISoldier>(Controller->GetPawn());
	if (!IsValid(Soldier))
	{
		return;
	}

	FVector			AILocation	= Soldier->GetActorLocation();
	AILocation.Z -= Soldier->GetHalfHeight();

	FCollisionQueryParams param(NAME_None, false, Soldier);

	UAIState* AIState = Soldier->GetState<UAIState>();

	if (!IsValid(AIState))
	{
		return;
	}

	FHitResult result;
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, AILocation, AILocation, FQuat::Identity, ECC_GameTraceChannel6, FCollisionShape::MakeSphere(AIState->mTraceDistance), param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugSphere(GetWorld(), AILocation, 
		AIState->mTraceDistance, 20, DrawColor, false,
		0.35f);

#endif

	if (IsCollision)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"),
			nullptr);
	}
}
