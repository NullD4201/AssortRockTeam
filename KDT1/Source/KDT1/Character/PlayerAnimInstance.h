// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

UCLASS()
class KDT1_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

public:
	UPlayerAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mMoveSpeed;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mMoveDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	bIsSprinting;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool    bIsTargetLock;
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// float		mOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage*		mSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mDodgeMontageArray;

	int32	mAttackIndex;

	bool	mAttackEnable;
	bool	mDodgeEnable;
	bool    mSprintEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType		mAnimType;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlaySprint();
	void PlaySprintEnd();
	void PlayDodgeMontage(int8 index);
	void PlaySkillMontage();
	void TargetLock();
	EPlayerAnimType GetAnimType()
	{
		return mAnimType;
	}

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_SkillEnd();

	UFUNCTION()
	void AnimNotify_AttackCoolDown();

	UFUNCTION()
	void AnimNotify_DodgeCoolDown();

	UFUNCTION()
	void AnimNotify_DodgeFinish();
};
