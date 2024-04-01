// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIPawn.h"
#include "SoldierPawn.generated.h"

struct FSoldierInfo : public FAIInfo
{
	int32		mAttackPoint;
	int32		mArmorPoint;
	int32		mHP;
	int32		mHPMax;
	int32		mMP;
	int32		mMPMax;
	float		mAttackDistance;
};


USTRUCT(BlueprintType)
struct FSoldierData : public FTableRowBase
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	int32		mAttackPoint;

	UPROPERTY(EditAnywhere)
	int32		mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32		mHPMax;

	UPROPERTY(EditAnywhere)
	int32		mMPMax;

	UPROPERTY(EditAnywhere)
	float		mMoveSpeed;

	UPROPERTY(EditAnywhere)
	float		mAttackDistance;

	UPROPERTY(EditAnywhere)
	float		mTraceDistance;
};

UCLASS()
class KDT1_API ASoldierPawn : public AAIPawn
{
	GENERATED_BODY()

protected:
	static UDataTable*	mSoldierDataTable;

public:
	static const FSoldierData*	FindSoldierData(const FString& Name);

	ASoldierPawn();

protected:
	class USoldierAnimInstance*		mAnimInst;
	FString		mTableRowName;
	class USoldierState*	mSoldierState;
	TArray<UMaterialInstanceDynamic*> mMaterialArray;

	bool	mHitEnable = false;
	float	mHitTime = 0.f;
	float	mHitDuration = 2.1f;

public:
	virtual void ChangeAIAnimType(uint8 AnimType) override;

protected:
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NormalAttack();
	virtual void Skill();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
