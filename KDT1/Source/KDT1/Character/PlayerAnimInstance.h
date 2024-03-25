// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

/**
 *
 */
UCLASS()
class KDT1_API UPlayerAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;
	//TArray<UAnimMontage*>

	// 공격 몽타주를 재생하기 위한 인덱스이다.
	int32	mAttackIndex;

	// 현재 공격가능한 상황인지를 판단하는 변수이다.
	bool	mAttackEnable;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	UPlayerAnimInstance();

public:
	void PlayAttackMontage();

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnable();

	UFUNCTION()
	void AnimNotify_AttackEnd();

private:

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly, Category = Attack, Meta = (AllowPrivateAccess = true))
	UAnimMontage* AttackMontage;
};