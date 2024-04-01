// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierAnimInstance.h"

#include "SoldierPawn.h"

void USoldierAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	mAnimType = ESoldierAnimType::Idle;
}

void USoldierAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);
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

void USoldierAnimInstance::AnimNotify_Skill()
{
	ASoldierPawn* Pawn = Cast<ASoldierPawn>(TryGetPawnOwner());
	Pawn->Skill();
	mAnimType = ESoldierAnimType::Skill;
}

void USoldierAnimInstance::AnimNotify_SkillEnd()
{
	ASoldierPawn* Pawn = Cast<ASoldierPawn>(TryGetPawnOwner());
	// Pawn->();
	mAnimType = ESoldierAnimType::Attack;
}
