// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_Patrol.h"

#include "AIController.h"
#include "Blueprint/AIBlueprintHelperLibrary.h"
#include "KDT1/AI/AIPawn.h"
#include "KDT1/AI/SoldierAnimInstance.h"

UBTTask_Patrol::UBTTask_Patrol()
{
	NodeName = TEXT("Patrol");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_Patrol::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::ExecuteTask(OwnerComp, NodeMemory);

	UE_LOG(KDT1, Warning, TEXT("Patrol Execute"));

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		return EBTNodeResult::Failed;
	}

	if (Pawn->IsPatrolPointEmpty())
	{
		return EBTNodeResult::Failed;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (IsValid(Target))
	{
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	FVector Point = Pawn->GetPatrolPoint();
	UAIBlueprintHelperLibrary::SimpleMoveToLocation(Controller, Point);

	Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Walk);

	return EBTNodeResult::InProgress;
}

void UBTTask_Patrol::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(KDT1, Warning, TEXT("Patrol Tick"));

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		Controller->StopMovement();
		
		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (IsValid(Target))
	{
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);

		return;
	}

	FVector	Dir = Pawn->GetMovementComponent()->Velocity;
	Dir.Z = 0.f;
	Dir.Normalize();

	Pawn->SetActorRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));
	
	FVector	AILocation = Pawn->GetActorLocation();
	FVector	TargetLocation = Target->GetActorLocation();
	AILocation.Z -= Pawn->GetHalfHeight();
	
	float	Distance = FVector::Distance(AILocation, TargetLocation);
	if (Distance <= 50.f)
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Succeeded);
		Controller->StopMovement();
		Pawn->ChangeAIAnimType((uint8)ESoldierAnimType::Idle);
		Pawn->NextPatrolPointIndex();
	}
}
