// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"

#include "MainCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mDodgeEnable = true;
	mSprintEnable = true;
	bIsSprinting = false;
	bIsTargetLock = false;
	mSprintMaxWalkSpeed = 600.f;
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
			//mMoveSpeed /= Movement->MaxWalkSpeed;

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

	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		mAttackEnable = false;
		mDodgeEnable = false;
		mAnimType = EPlayerAnimType::Attack;

		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		Montage_Play(mAttackMontageArray[mAttackIndex]);
		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
	}
}

void UPlayerAnimInstance::PlaySprint()
{
	if (bIsTargetLock == true)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("Sprint"));

	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			if (!mSprintEnable)
				return;

			//mAnimType = EPlayerAnimType::Run;
			bIsSprinting = true;
			//mSprintMaxWalkSpeed = Movement->MaxWalkSpeed;
			//Movement->MaxWalkSpeed = 1000.f;
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("SprintFunc"));

			PlayerCharacter->StartSprinting();
		}
	}
}

void UPlayerAnimInstance::PlaySprintEnd()
{
	if (bIsTargetLock == true)
		return;

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("SprintEnd"));

	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			bIsSprinting = false;

			//mAnimType = EPlayerAnimType::Idle;
			//Movement->MaxWalkSpeed = mSprintMaxWalkSpeed;
			GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Blue, TEXT("SprintFunc End"));

			PlayerCharacter->StopSprinting();
		}
	}
}

void UPlayerAnimInstance::PlayDodgeMontage(int8 index)
{
	if (!mDodgeEnable)
		return;
	
	mAttackEnable = false;
	mDodgeEnable = false;
	mAnimType = EPlayerAnimType::Dodge;

	Montage_SetPosition(mDodgeMontageArray[index], 0.f);
	Montage_Play(mDodgeMontageArray[index]);
	
}

void UPlayerAnimInstance::PlaySkillMontage()
{
	if (mAnimType == EPlayerAnimType::Dodge || mAnimType == EPlayerAnimType::Attack)
		return;

	if (!Montage_IsPlaying(mSkillMontage))
	{
		mAttackEnable = false;
		mDodgeEnable = false;
		mAnimType = EPlayerAnimType::Skill;

		Montage_SetPosition(mSkillMontage, 0.f);
		Montage_Play(mSkillMontage);
	}
}

void UPlayerAnimInstance::TargetLock()
{
	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());
	UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();
	
	// Tap 키 눌렀을 때 움직임 변하도록만 간단히 만듬
	if (bIsTargetLock == true)
	{
		bIsTargetLock = false;
		Movement->bUseControllerDesiredRotation = false;
		Movement->bOrientRotationToMovement = true;
	}
	else
	{
		bIsTargetLock = true;
		Movement->bUseControllerDesiredRotation = true;
		Movement->bOrientRotationToMovement = false;
	}
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

void UPlayerAnimInstance::AnimNotify_AttackCoolDown()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mDodgeEnable = true;

	mAnimType = EPlayerAnimType::CoolDown;
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;
	mDodgeEnable = true;

	mAnimType = EPlayerAnimType::Idle;
}

void UPlayerAnimInstance::AnimNotify_SkillEnd()
{
}

void UPlayerAnimInstance::AnimNotify_DodgeCoolDown()
{
	mAnimType = EPlayerAnimType::CoolDown;
	mAttackEnable = true;
	mDodgeEnable = true;
	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_DodgeFinish()
{
	mAnimType = EPlayerAnimType::Idle;

	mAttackEnable = true;
	mDodgeEnable = true;
}

