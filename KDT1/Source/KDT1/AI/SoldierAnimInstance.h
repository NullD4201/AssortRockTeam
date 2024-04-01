// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Animation/AnimInstance.h"
#include "SoldierAnimInstance.generated.h"

UENUM(BlueprintType)
enum class ESoldierAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Attack,
	Death,
	Skill
};

UCLASS()
class KDT1_API USoldierAnimInstance : public UAnimInstance
{
	GENERATED_BODY()

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	ESoldierAnimType	mAnimType;
	
public:
	void ChangeAnimType(ESoldierAnimType AnimType)
	{
		mAnimType = AnimType;
	}

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaSeconds) override;

	UFUNCTION()
	void AnimNotify_Attack();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_DeathEnd();

	UFUNCTION()
	void AnimNotify_Skill();

	UFUNCTION()
	void AnimNotify_SkillEnd();	
};
