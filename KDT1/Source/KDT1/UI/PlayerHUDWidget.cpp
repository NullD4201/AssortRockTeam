// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUDWidget.h"

#include "Animation/WidgetAnimation.h"

void UPlayerHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	mWeaponType = Cast<UImage>(GetWidgetFromName(TEXT("WeaponType")));
	mHp = Cast<UProgressBar>(GetWidgetFromName("HP"));
	mCombo = Cast<UTexture2D>(GetWidgetFromName("Combo"));
	// mScore = Cast<UTextBlock>(GetWidgetFromName("ScoreText"));

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
	case EPlayerWeaponType::Sword:
	default:
		mWeaponType->SetBrushFromTexture(mWeaponSword);
		break;
	}
}

void UPlayerHUDWidget::SetHp(int32 Hp, int32 HpMax)
{
	float mHpPercent = Hp / HpMax;
	mHp->SetPercent(mHpPercent);
}

void UPlayerHUDWidget::ShowCombo()
{
	PlayAnimationForward(ComboAnimation);
}