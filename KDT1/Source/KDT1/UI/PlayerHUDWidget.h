// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "Blueprint/UserWidget.h"
#include "Components/Image.h"
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

	virtual void NativeConstruct() override;

public:
	void SetWeaponType(EPlayerWeaponType Weapon);
	
};
