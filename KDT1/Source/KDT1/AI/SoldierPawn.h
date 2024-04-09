// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIPawn.h"
#include "SoldierPawn.generated.h"

struct FSoldierInfo : public FAIInfo
{
	int32		mAttackPoint;
	int32		mArmorPoint;
	int32		mHp;
	int32		mHpMax;
	float		mAttackDistance;
};

USTRUCT(BlueprintType)
struct FSoldierData : public FTableRowBase
{
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	int32		mAttackPoint;

	UPROPERTY(EditAnywhere)
	int32		mArmorPoint;

	UPROPERTY(EditAnywhere)
	int32		mHpMax;

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
	static UDataTable* mSoldierDataTable;

public:
<<<<<<< Updated upstream
	// static const FSoldierData* FindSoldierData(const FString& Name);
=======
	static const FSoldierData* FindSoldierData(const FString& Name);
>>>>>>> Stashed changes

	ASoldierPawn();

	virtual void ChangeAIAnimType(uint8 AnimType);

protected:
	class USoldierAnimInstance* mAnimInstance;
	FString		mTableRowName;
	class USoldierState* mSoldierState;
	TArray<UMaterialInstanceDynamic*> mMaterialArray;

	bool mHitEnable = false;
	float mHitTime = 0.f;
	float mHitDuration = 2.f;

<<<<<<< Updated upstream
=======
	float	HalfAngle;
	float	DeltaAngle;
	float	ExternalRadius;

>>>>>>> Stashed changes
	virtual void BeginPlay() override;

public:
	virtual void OnConstruction(const FTransform& Transform) override;
	virtual void Tick(float DeltaSeconds) override;
	virtual void NormalAttack();
	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};
