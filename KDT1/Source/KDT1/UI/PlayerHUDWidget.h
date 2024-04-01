// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Engine/DataTable.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UImage* mWeaponType;

	UTexture2D* mWeaponSword;

	UTexture2D* mWeaponSpear;

	UTexture2D* mWeaponBow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProgressBar* mHp;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* mCombo;

	// UPROPERTY(EditAnywhere, BlueprintReadOnly)
	// UTextBlock* mScore;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(BindWidgetAnim), Transient)
	class UWidgetAnimation* ComboAnimation;

	virtual void NativeConstruct() override;

public:
	void SetWeaponType(EPlayerWeaponType Weapon);
	void SetHp(int32 Hp, int32 HpMax);
	void ShowCombo();
};
