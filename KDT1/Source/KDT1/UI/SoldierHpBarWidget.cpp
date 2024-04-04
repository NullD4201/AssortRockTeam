// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierHpBarWidget.h"

#include "KDT1/AI/SoldierState.h"

void USoldierHpBarWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mHp = Cast<UProgressBar>(GetWidgetFromName("SoldierHpProgressBar"));
}

void USoldierHpBarWidget::SetHp()
{
	mHp->SetPercent(mSoldierState->mHP * 1.f / mSoldierState->mHPMax);
}
