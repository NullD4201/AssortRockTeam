// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MainCharacter.h"
#include "../MainPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackEnable = true;
	mAttackIndex = 0;
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

			// 캐릭터가 땅을 밟고 있는지 판단한다.
			// IsMovingOnGround : 캐릭터가 땅을 밟고 있으면 true,
			// 아니면 false를 반환한다.
			mOnGround = Movement->IsMovingOnGround();

		}

		// 이 애님인스턴스를 가지고 있는 캐릭터로부터 해당 캐릭터를 컨트롤 하고 있는 플레이어
		// 컨트롤러를 얻어온다.
		AMainPlayerController* Controller = PlayerCharacter->GetController<AMainPlayerController>();

		// 위에서 얻어온 컨트롤러가 유효한지 체크한다.
		if (IsValid(Controller))
		{
			mMoveDir = Controller->GetMoveDir();
		}
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!mAttackEnable)
		return;

	mAttackEnable = false;

	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		
		Montage_Play(mAttackMontageArray[mAttackIndex]);

		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackStart()
{
	// 데미지 주는 함수 호출용	
}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;
}

void UPlayerAnimInstance::AnimNotify_CoolDown()
{
	mAttackEnable = true;

	mAttackIndex = 0;
}

void UPlayerAnimInstance::AnimNotify_CanAttack()
{
	//mAttackEnable = true;
}
