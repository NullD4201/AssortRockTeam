// Fill out your copyright notice in the Description page of Project Settings.


#include "BTService_DetectTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "KDT1/AI/AIPawn.h"

UBTService_DetectTarget::UBTService_DetectTarget()
{
	NodeName = TEXT("DetectTarget");
	Interval = 0.5f;
	RandomDeviation = 0.1f;
}

void UBTService_DetectTarget::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		return;
	}

	FVector AILocation = Pawn->GetActorLocation();
	AILocation.Z = Pawn->GetHalfHeight();

	FCollisionQueryParams	param(NAME_None, false, Pawn);
	UAIState* AIState = Pawn->GetState<UAIState>();
	if (!IsValid(AIState))
	{
		return;
	}

	FHitResult	result;
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, AILocation, AILocation, FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(AIState->mTraceDistance), param);

#if ENABLE_DRAW_DEBUG
	FColor DrawColor = IsCollision ? FColor::Red  : FColor::Green;

	DrawDebugSphere(GetWorld(), AILocation, AIState->mTraceDistance, 20, DrawColor, false, 0.35f);
#endif

	if (IsCollision)
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), result.GetActor());
	}
	else
	{
		Controller->GetBlackboardComponent()->SetValueAsObject(TEXT("Target"), nullptr);
	}
}
