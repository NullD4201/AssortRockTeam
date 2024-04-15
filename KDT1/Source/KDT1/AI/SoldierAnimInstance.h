// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SoldierAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ESoldierAnimType : uint8
{
	Idle,
	Run,
	Attack,
	Death
};

UCLASS()
class KDT1_API USoldierAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESoldierAnimType	mAnimType;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float		mMoveDir;

public:
	void ChangeAnimType(ESoldierAnimType Type)
	{
		mAnimType = Type;
	}

	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();
};
