// Fill out your copyright notice in the Description page of Project Settings.


#include "SwordCharacter.h"

ASwordCharacter::ASwordCharacter()
{
	mCameraArm->SetRelativeLocation(FVector(0., 0., 70.));
	
	GetMesh()->SetRelativeLocation(FVector(0., 0., -96.));
	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/InfinityBladeWeapons/Weapons/Blade/Swords/Blade_BlackKnight/SK_Blade_BlackKnight.SK_Blade_BlackKnight'"));
	if (SwordAsset.Succeeded())
	{
		mMesh->SetSkeletalMesh(SwordAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SwordSekeltalAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/BowAnimation/Character/SKB/SKM_Manny_Simple.SKM_Manny_Simple'"));
	if (SwordSekeltalAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SwordSekeltalAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> SwordAnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Main/Animation/Sword/ABP_SwordRetarget.ABP_SwordRetarget_C'"));
	if (SwordAnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SwordAnimInstance.Class);
	}
}
