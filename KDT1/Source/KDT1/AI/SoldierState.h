// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIState.h"
#include "SoldierState.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API USoldierState : public UAIState
{
	GENERATED_BODY()

public:
	USoldierState();

	UPROPERTY(EditAnywhere)
	int32		mAttackPoint;

	UPROPERTY(EditAnywhere)
	int32		mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32		mHP;

	UPROPERTY(EditAnywhere)
	int32		mHPMax;

	UPROPERTY(EditAnywhere)
	int32		mMP;

	UPROPERTY(EditAnywhere)
	int32		mMPMax;

	UPROPERTY(EditAnywhere)
	float		mAttackDistance;

protected:
	virtual void BeginPlay() override;
};
