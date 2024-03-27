// Fill out your copyright notice in the Description page of Project Settings.


#include "SpearCharacter.h"

ASpearCharacter::ASpearCharacter()
{
	mCameraArm->SetRelativeLocation(FVector(0., 0., 70.));
	
	GetMesh()->SetRelativeLocation(FVector(0., 0., -96.));
	GetMesh()->SetRelativeRotation(FRotator(0., -90., 0.));
	
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SpearAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/SpearAnimation/Demo/Character/Mesh/Weapom_Spear.Weapom_Spear'"));
	if (SpearAsset.Succeeded())
	{
		mMesh->SetSkeletalMesh(SpearAsset.Object);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> SpearSekeltalAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/SpearAnimation/Demo/Character/Mesh/SK_Mannequin_Spear.SK_Mannequin_Spear'"));
	if (SpearSekeltalAsset.Succeeded())
	{
		GetMesh()->SetSkeletalMesh(SpearSekeltalAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> SpearAnimInstance(TEXT("/Script/Engine.AnimBlueprint'/Game/Main/Animation/Spear/ABP_TestSpear.ABP_TestSpear_C'"));
	if (SpearAnimInstance.Succeeded())
	{
		GetMesh()->SetAnimInstanceClass(SpearAnimInstance.Class);
	}
}
