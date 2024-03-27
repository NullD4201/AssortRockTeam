// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MainCharacter.h"
#include "../MainPlayerController.h"

UPlayerAnimInstance::UPlayerAnimInstance()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mAnimType = EPlayerType::Idle;
	mDodgeEnable = true;
}

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("mAttackEnable : %i"), mAttackEnable));
	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, FString::Printf(TEXT("bCanMove : %i"), bCanMove));

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

			mMoveDir = CalculateDirection(Movement->Velocity, PlayerCharacter->GetActorRotation());
		}

		// 이 애님인스턴스를 가지고 있는 캐릭터로부터 해당 캐릭터를 컨트롤 하고 있는 플레이어
		// 컨트롤러를 얻어온다.
		//AMainPlayerController* Controller = PlayerCharacter->GetController<AMainPlayerController>();

		//// 위에서 얻어온 컨트롤러가 유효한지 체크한다.
		//if (IsValid(Controller))
		//{
		//	mMoveDir = Controller->GetMoveDir();
		//}
	}
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	if (!mAttackEnable)
		return;

	if (!Montage_IsPlaying(mAttackMontageArray[mAttackIndex]))
	{
		mAttackEnable = false;
		mDodgeEnable = false;
		mAnimType = EPlayerType::Idle;

		Montage_SetPosition(mAttackMontageArray[mAttackIndex], 0.f);
		
		Montage_Play(mAttackMontageArray[mAttackIndex]);

		mAttackIndex = (mAttackIndex + 1) % mAttackMontageArray.Num();
	}
}

void UPlayerAnimInstance::AnimNotify_AttackStart()
{	
	// 데미지 콜리전 함수 호출 용;

}

void UPlayerAnimInstance::AnimNotify_AttackEnd()
{
	mAttackEnable = true;

}

void UPlayerAnimInstance::AnimNotify_CanMove()
{
	mAnimType = EPlayerType::AttackCoolDown;

	//bIsDodging = false;
	mDodgeEnable = true;
}

void UPlayerAnimInstance::AnimNotify_CoolDown()
{
	mAttackEnable = true;

	mAttackIndex = 0;

}

void UPlayerAnimInstance::AnimNotify_EndMontage()
{
	//mAttackEnable = true;

	mAnimType = EPlayerType::Idle;
}

void UPlayerAnimInstance::AnimNotify_DodgeCoolDown()
{
	mAttackEnable = true;
	mAttackIndex = 0;
	mDodgeEnable = true;

	mAnimType = EPlayerType::DodgeCoolDown;
}

void UPlayerAnimInstance::AnimNotify_DodgeFinish()
{
	mAnimType = EPlayerType::Idle;

	//bIsDodging = false;
}

void UPlayerAnimInstance::PlayDodgeMontage(int8 index)
{
	if (!mDodgeEnable)
		return;

	mAnimType = EPlayerType::Idle;

	mAttackEnable = false;

	mDodgeEnable = false;

	Montage_SetPosition(mDodgeMontageArray[index], 0.f);

	Montage_Play(mDodgeMontageArray[index]);


}