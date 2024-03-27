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
	
	// UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	// float		mOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UAnimMontage*		mSkillMontage;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;

	int32	mAttackIndex;

	bool	mAttackEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType		mAnimType;

public:
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	void PlayAttackMontage();
	void PlayDodgeMontage();
	void PlaySkillMontage();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_CoolDown();
};
