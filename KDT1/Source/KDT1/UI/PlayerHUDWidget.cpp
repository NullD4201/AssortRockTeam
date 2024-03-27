// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mWeaponType = Cast<UImage>(GetWidgetFromName(TEXT("WeaponType")));

	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponSword(TEXT("/Script/Engine.Texture2D'/Game/Main/Textures/sword.sword'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponSpear(TEXT("/Script/Engine.Texture2D'/Game/Main/Textures/stick.stick'"));
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponBow(TEXT("/Script/Engine.Texture2D'/Game/Main/Textures/bow.bow'"));

	mWeaponSword = WeaponSword.Object;
	mWeaponSpear = WeaponSpear.Object;
	mWeaponBow = WeaponBow.Object;
}

void UPlayerHUDWidget::SetWeaponType(EPlayerWeaponType Weapon)
{
	switch (Weapon)
	{
	case EPlayerWeaponType::Spear:
		mWeaponType->SetBrushFromTexture(mWeaponSpear);
		break;
	case EPlayerWeaponType::Bow:
		mWeaponType->SetBrushFromTexture(mWeaponBow);
		break;
	case EPlayerWeaponType::Sword:
	default:
		mWeaponType->SetBrushFromTexture(mWeaponSword);
		break;
	}
}