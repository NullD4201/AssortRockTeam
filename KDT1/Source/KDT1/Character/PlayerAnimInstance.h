// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "PlayerAnimInstance.generated.h"

// BlueprintType : 블루프린트에서 사용할 수 있는 타입으로 만들어준다.
UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Default,
	Jump,
	Fall,
	Death,
	Skill
};

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

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mSkillMontageArray;

	// 공격 몽타주를 재생하기 위한 인덱스이다.
	int32	mAttackIndex;
	
	// 현재 공격가능한 상황인지를 판단하는 변수이다.
	bool	mAttackEnable;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	EPlayerAnimType	mAnimType;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);
	UPlayerAnimInstance();

public:
	void PlayAttackMontage();
	void PlaySkillMontage(int32 Index);

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