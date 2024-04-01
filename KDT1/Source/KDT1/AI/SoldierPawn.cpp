// Fill out your copyright notice in the Description page of Project Settings.


#include "SoldierPawn.h"

#include "SoldierAIController.h"
#include "SoldierAnimInstance.h"
#include "SoldierState.h"

UDataTable* ASoldierPawn::mSoldierDataTable = nullptr;

const FSoldierData* ASoldierPawn::FindSoldierData(const FString& Name)
{
	return mSoldierDataTable->FindRow<FSoldierData>(*Name, TEXT(""));
}

ASoldierPawn::ASoldierPawn()
{
	PrimaryActorTick.bCanEverTick = true;

	mState = CreateDefaultSubobject<USoldierState>(TEXT("SoldierState"));

	mSoldierState = Cast<USoldierState>(mState);

	AIControllerClass = ASoldierAIController::StaticClass();

	mCapsule->SetCollisionProfileName(TEXT("Enemy"));
	
	static ConstructorHelpers::FObjectFinder<UDataTable> SoldierTable(TEXT("/Script/Engine.DataTable'/Game/Main/DT_SoldierData.DT_SoldierData'"));

	if (!IsValid(mSoldierDataTable) && SoldierTable.Succeeded())
	{
		mSoldierDataTable = SoldierTable.Object;
	}
}

void ASoldierPawn::ChangeAIAnimType(uint8 AnimType)
{
	mAnimInst->ChangeAnimType((ESoldierAnimType) AnimType);
}

void ASoldierPawn::BeginPlay()
{
	Super::BeginPlay();

	mAIInfo = new FSoldierInfo;

	FSoldierInfo* SoldierInfo = (FSoldierInfo*)mAIInfo;

	const FSoldierData* Data = FindSoldierData(mTableRowName);
	mAttackPoint = Data->mAttackPoint;

	SoldierInfo->mAttackPoint = Data->mAttackPoint;
	SoldierInfo->mArmorPoint = Data->mArmorPoint;
	SoldierInfo->mHP = Data->mHPMax;
	SoldierInfo->mHPMax = Data->mHPMax;
	SoldierInfo->mMP = Data->mMPMax;
	SoldierInfo->mMPMax = Data->mMPMax;
	SoldierInfo->mMoveSpeed = Data->mMoveSpeed;
	SoldierInfo->mAttackDistance = Data->mAttackDistance;
	SoldierInfo->mTraceDistance = Data->mTraceDistance;

	mMovement->MaxSpeed = SoldierInfo->mMoveSpeed;

	mAnimInst = Cast<USoldierAnimInstance>(mMesh->GetAnimInstance());
}

void ASoldierPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);

	mState->mDataTableRowName = mTableRowName;

	int32 ElementCount = mMesh->GetNumMaterials();
	for (int32 i = 0; i < ElementCount; i++)
	{
		UMaterialInstanceDynamic* Mtrl = mMesh->CreateDynamicMaterialInstance(i);

		mMaterialArray.Add(Mtrl);
	}
}

void ASoldierPawn::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (mHitEnable)
	{
		mHitTime += DeltaSeconds;

		if (mHitTime >= mHitDuration)
		{
			mHitEnable = false;
			mHitTime = 0.f;

			for (auto Mtrl : mMaterialArray)
			{
				Mtrl->SetScalarParameterValue(TEXT("HitEnable"), 0.f);
			}
		}
	}
}

void ASoldierPawn::NormalAttack()
{
	GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Red, TEXT("NormalAttack"));
}

void ASoldierPawn::Skill()
{
}

float ASoldierPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	mSoldierState->mHP -= DamageAmount;

	if (!mHitEnable)
	{
		if (mSoldierState->mHP <= 0)
		{
			mAnimInst->ChangeAnimType(ESoldierAnimType::Death);
		}

		mHitEnable = true;
		mHitTime = 0.f;
	}

	return DamageAmount;
}
