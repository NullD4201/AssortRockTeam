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
	int32		mHp;
	
	UPROPERTY(EditAnywhere)
	int32		mHpMax;
	
	UPROPERTY(EditAnywhere)
	float		mAttackDistance;
	
protected:
	virtual void BeginPlay() override;
};
