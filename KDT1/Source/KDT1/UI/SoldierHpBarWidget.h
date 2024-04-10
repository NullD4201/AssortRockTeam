// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/ProgressBar.h"
#include "SoldierHpBarWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API USoldierHpBarWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProgressBar* mHp;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	class USoldierState*	mSoldierState;

	virtual void NativeConstruct() override;

public:
	void SetHp();
};
