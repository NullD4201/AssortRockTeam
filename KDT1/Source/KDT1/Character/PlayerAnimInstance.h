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
	
public :
	UPlayerAnimInstance();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveSpeed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	float	mMoveDir;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	bool	mOnGround;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TArray<TObjectPtr<UAnimMontage>>	mAttackMontageArray;

	bool mAttackEnable;
	int32 mAttackIndex;

public:
	virtual void NativeInitializeAnimation();
	virtual void NativeUpdateAnimation(float DeltaSeconds);

	void PlayAttackMontage();

public :
	UFUNCTION()
	void AnimNotify_AttackStart();

	UFUNCTION()
	void AnimNotify_AttackEnd();

	UFUNCTION()
	void AnimNotify_CoolDown();

	UFUNCTION()
	void AnimNotify_CanAttack();
};
