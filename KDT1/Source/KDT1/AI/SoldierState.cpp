// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierState.h"

#include "SoldierPawn.h"

USoldierState::USoldierState()
{
}

void USoldierState::BeginPlay()
{
	Super::BeginPlay();

	const FSoldierData* Data = ASoldierPawn::FindSoldierData(mDataTableRowName);

	if (Data)
	{
		mMoveSpeed = Data->mMoveSpeed;
		mTraceDistance = Data->mTraceDistance;
		mAttackPoint = Data->mAttackPoint;
		mArmorPoint = Data->mArmorPoint;
		mHP = Data->mHPMax;
		mHPMax = Data->mHPMax;
		mMP = Data->mMPMax;
		mMPMax = Data->mMPMax;
		mAttackDistance = Data->mAttackDistance;
	}
}
