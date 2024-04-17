// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "Kismet/KismetMathLibrary.h"
#include "MainCharacter.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mDodgeEnable = true;
	mSprintEnable = true;
	bIsSprinting = false;
	bIsTargetLock = false;
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

			mMoveDir = UKismetAnimationLibrary::CalculateDirection(Movement->Velocity, PlayerCharacter->GetActorRotation());
		}
	}
}

// 적을 찾는 함수
 AActor* UPlayerAnimInstance::FindEnemy()
{
	// 플레이어의 위치와 방향을 가져옵니다.
	FVector PlayerLocation = GetOwningActor()->GetActorLocation();
	FRotator PlayerRotation = GetOwningActor()->GetActorRotation();

	// 일정 범위 내의 모든 적을 찾습니다.
	TArray<AActor*> FoundEnemies;
	UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAISoldier::StaticClass(), FoundEnemies);

	AActor* closestEnemy = nullptr;
	float closestDistance = FLT_MAX;

	// 가장 가까운 적을 찾습니다.
	for (AActor* enemy : FoundEnemies)
	{
		float distance = FVector::Dist(PlayerLocation, enemy->GetActorLocation());
		if (distance < closestDistance)
		{
			closestDistance = distance;
			closestEnemy = enemy;
		}
	}

	return closestEnemy;
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!mAttackEnable)
	{
		return;
	}

	// 적을 찾습니다.
	AActor* enemy = FindEnemy();
	if (enemy)
	{
		// 플레이어가 적을 바라보도록 합니다.
		FRotator lookAtRotation = UKismetMathLibrary::FindLookAtRotation(GetOwningActor()->GetActorLocation(), enemy->GetActorLocation());
		GetOwningActor()->SetActorRotation(lookAtRotation);
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

	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			if (!mSprintEnable)
				return;

			bIsSprinting = true;
		}
	}
}

void UPlayerAnimInstance::PlaySprintEnd()
{
	if (bIsTargetLock == true)
		return;

	AMainCharacter* PlayerCharacter = Cast<AMainCharacter>(TryGetPawnOwner());

	if (IsValid(PlayerCharacter))
	{
		UCharacterMovementComponent* Movement = PlayerCharacter->GetCharacterMovement();

		if (IsValid(Movement))
		{
			bIsSprinting = false;

			mAnimType = EPlayerAnimType::Idle;
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
	if (bIsTargetLock == true)
	{
		bIsTargetLock = false;
	}
	else
	{
		bIsTargetLock = true;
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


