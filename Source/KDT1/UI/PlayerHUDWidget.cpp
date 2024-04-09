// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

UPlayerHUDWidget::UPlayerHUDWidget(const FObjectInitializer& ObjectInitializer) : Super(ObjectInitializer)
{
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponSword(TEXT("/Game/Main/Textures/sword.sword"));
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponSpear(TEXT("/Game/Main/Textures/stick.stick"));
	static ConstructorHelpers::FObjectFinder<UTexture2D>
		WeaponBow(TEXT("/Game/Main/Textures/bow.bow"));

	mWeaponSword = WeaponSword.Object;
	mWeaponSpear = WeaponSpear.Object;
	mWeaponBow = WeaponBow.Object;
}

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mWeaponType = Cast<UImage>(GetWidgetFromName(TEXT("WeaponType")));
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