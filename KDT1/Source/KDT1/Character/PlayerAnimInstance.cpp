// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "MainCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mAnimType = EPlayerAnimType::Idle;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			mMoveSpeed = Movement->Velocity.Length();
			mMoveSpeed /= Movement->MaxWalkSpeed;

			mMoveDir = CalculateDirection(Movement->Velocity, PlayerCharacter->GetActorRotation());
		}
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!mAttackEnable)
	{
		return;
	}

	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Montage2"));
	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		mAttackEnable = false;
		mAnimType = EPlayerAnimType::Attack;

		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		Montage_Play(mAttackMontageArray[mAttackIndex]);
		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
	}
	else
	{
		GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, FString::FromInt(mAttackIndex));
	}
}

void UPlayerAnimInstance::PlayDodgeMontage()
{
}

void UPlayerAnimInstance::PlaySkillMontage()
{
}

void UPlayerAnimInstance::AnimNotify_Attack()
{
	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	PlayerCharacter->NormalAttack();
}

void UPlayerAnimInstance::AnimNotify_AttackEnable()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;
	mAnimType = EPlayerAnimType::Idle;
}

void UPlayerAnimInstance::AnimNotify_CoolDown()
{
	mAttackEnable = true;
	mAttackIndex = 0;
}
