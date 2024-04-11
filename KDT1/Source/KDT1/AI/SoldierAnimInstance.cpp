// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstance.h"

#include "AISoldier.h"
#include "SoldierPawn.h"

void USoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = ESoldierAnimType::Idle;
}

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AAISoldier* AISoldier = Cast<AAISoldier>(TryGetPawnOwner());

	if (AISoldier)
	{
		UPawnMovementComponent* MovementComponent = AISoldier->GetMovementComponent();

		if (MovementComponent)
		{
			mMoveDir = UKismetAnimationLibrary::CalculateDirection(MovementComponent->Velocity, AISoldier->GetActorRotation());
		}
	}
}

void USoldierAnimInstance::AnimNotify_Attack()
{
	ASoldierPawn* Pawn = Cast<ASoldierPawn>(TryGetPawnOwner());

	Pawn->NormalAttack();
}

void USoldierAnimInstance::AnimNotify_AttackEnd()
{
	ASoldierPawn* Pawn = Cast<ASoldierPawn>(TryGetPawnOwner());

	Pawn->SetAttackEnd(true);
}

void USoldierAnimInstance::AnimNotify_DeathEnd()
{
	ASoldierPawn* Pawn = Cast<ASoldierPawn>(TryGetPawnOwner());
}
