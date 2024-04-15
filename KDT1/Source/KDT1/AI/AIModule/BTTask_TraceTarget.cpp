// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_TraceTarget.h"

#include "AIController.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "../AIPawn.h"
#include "../SoldierAnimInstance.h"
#include "KDT1/AI/SoldierPawn.h"
#include "KDT1/AI/SoldierState.h"

UBTTask_TraceTarget::UBTTask_TraceTarget()
{
	NodeName = TEXT("TraceTarget");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_TraceTarget::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	UAIBlueprintHelperLibrary::SimpleMoveToActor(Controller, Target);
	Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Run);

	return EBTNodeResult::InProgress;
}

void UBTTask_TraceTarget::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		Controller->StopMovement();
		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);
		return;
	}

	FVector Dir = Pawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;
	Dir.Normalize();

	Pawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));

	FVector AILocation = Pawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();
	AILocation.Z -= Pawn->GetHalfHeight();
	UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());
	if (IsValid(TargetCapsule))
	{
		TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
	}

	float Distance = FVector::Distance(AILocation, TargetLocation);
	USoldierState* State = Pawn->GetState<USoldierState>();
	if (Distance <= State->mAttackDistance)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);
	}
}

void UBTTask_TraceTarget::OnTaskFinished(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory,
	EBTNodeResult::Type TaskResult)
{
	Super::OnTaskFinished(OwnerComp, NodeMemory, TaskResult);
}
