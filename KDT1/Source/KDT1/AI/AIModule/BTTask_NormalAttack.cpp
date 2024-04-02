// Fill out your copyright notice in the Description page of Project Settings.


#include "BTTask_NormalAttack.h"

#include "AIController.h"
#include "KDT1/AI/AIPawn.h"
#include "KDT1/AI/SoldierAnimInstance.h"
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

	UE_LOG(KDT1, Warning, TEXT("Normal Execute"));

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
		Pawn->ChangeAIAnimType((uint8)ESoldierAnimType::Idle);

		return EBTNodeResult::Failed;
	}

	Pawn->ChangeAIAnimType((uint8) ESoldierAnimType::Attack);

	return EBTNodeResult::InProgress;
}

void UBTTask_NormalAttack::TickTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickTask(OwnerComp, NodeMemory, DeltaSeconds);

	UE_LOG(KDT1, Warning, TEXT("Normal Tick"));

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
		
		Pawn->ChangeAIAnimType((uint8)ESoldierAnimType::Idle);

		return;
	}

	if (Pawn->IsAttackEnd())
	{
		Pawn->SetAttackEnd(false);

		FVector AILocation = Pawn->GetActorLocation();
		FVector TargetLocation = Target->GetActorLocation();
		FVector Dir = TargetLocation - AILocation;
		Dir.Z = 0.0;
		AILocation.Z = Pawn->GetHalfHeight();
		UCapsuleComponent* TargetCapsule = Cast<UCapsuleComponent>(Target->GetRootComponent());
		if (IsValid(TargetCapsule))
		{
			TargetLocation.Z -= TargetCapsule->GetScaledCapsuleHalfHeight();
		}

		float Distance = FVector::Distance(AILocation, TargetLocation);
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
			Rot.Roll = 0.0;

			Pawn->SetActorRotation(Rot);
		}
	}
}
