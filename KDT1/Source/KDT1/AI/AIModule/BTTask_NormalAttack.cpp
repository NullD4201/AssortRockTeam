// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"

#include "../AIPawn.h"
#include "../SoldierAnimInstance.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "AIController.h"
#include "KDT1/AI/SoldierState.h"

UBTTask_NormalAttack::UBTTask_NormalAttack()
{
	NodeName = TEXT("NormalAttack");
	bNotifyTick = true;
	bNotifyTaskFinished = true;
}

EBTNodeResult::Type UBTTask_NormalAttack::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
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
	
	FVector AILocation = Pawn->GetActorLocation();
	FVector TargetLocation = Target->GetActorLocation();

	FVector Dir = TargetLocation - AILocation;
	FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();

	Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Attack);
	Pawn->SetActorRotation(Rot);

	return EBTNodeResult::InProgress;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	AAIController* Controller = OwnerComp.GetAIOwner();
	AAIPawn* Pawn = Cast<AAIPawn>(Controller->GetPawn());
	if (!IsValid(Pawn))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		
		return;
	}

	AActor* Target = Cast<AActor>(Controller->GetBlackboardComponent()->GetValueAsObject(TEXT("Target")));
	if (!IsValid(Target))
	{
		FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
		
		Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);

		return;
	}

	if (Pawn->IsAttackEnd())
	{
		Pawn->SetAttackEnd(false);

		FVector AILocation = Pawn->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();

		FVector Dir = TargetLocation - AILocation;
		Dir.Z = 0.;

		AILocation.Z = Pawn->GetHalfHeight();

		UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());
		if (!IsValid(TargetCapsule))
		{
			TargetLocation.Z = TargetCapsule->GetScaledCapsuleHalfHeight();
		}

		float	Distance = FVector::Distance(AILocation, TargetLocation);
		USoldierState* State = Pawn->GetState<USoldierState>();

		if (Distance > State->mAttackDistance)
		{
			FinishLatentTask(OwnerComp, EBTNodeResult::Failed);
			Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Idle);
		}
		else
		{
			FRotator Rot = FRotationMatrix::MakeFromX(Dir).Rotator();
			Rot.Pitch = 0.0;
			Rot.Roll = -10.0;

			Pawn->SetActorRotation(Rot);
		}
	}
}