// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "PlayerHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UPlayerHUDWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UImage* mWeaponType;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* mWeaponSword;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* mWeaponSpear;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTexture2D* mWeaponBow;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UProgressBar* mHealthBar;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UTextBlock* mHealthText;

	UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativeConstruct() override;

public:
	void SetWeaponType(EPlayerWeaponType Weapon);
	void SetHealth(int32 mHp);
};
