// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "AIState.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "GameFramework/FloatingPawnMovement.h"
#include "GameFramework/Pawn.h"
#include "AIPawn.generated.h"

struct FAIInfo
{
	float	mMoveSpeed;
	float	mTraceDistance;
};

UCLASS()
class KDT1_API AAIPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAIPawn();

protected:
	UPROPERTY(EditAnywhere)
	UCapsuleComponent* mCapsule;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere)
	USkeletalMeshComponent* mWeaponMesh;

	UPROPERTY(EditAnywhere)
	UFloatingPawnMovement* mMovement;

	UPROPERTY(EditAnywhere)
	UWidgetComponent* mHealthBar;

	UPROPERTY(EditAnywhere)
	class UAIState*		mState;
	
	FAIInfo* mAIInfo;

	bool	mAttackEnd;

	class AAISpawnPoint* mSpawnPoint;

	UPROPERTY(EditAnywhere)
	TArray<class APatrolPointActor*>	mPatrolArray;

	TArray<FVector>		mPatrolPointArray;

	int32	mPatrolIndex;
	int32	mPatrolDir;

	int32	mAttackPoint;
	int32	mArmorPoint;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	virtual void EndPlay(const EEndPlayReason::Type EndPlayReason) override;

public:
	template <typename T>
	T* GetAIInfo()
	{
		return (T*) mAIInfo;
	}

	template <typename T>
	T* GetState()
	{
		return Cast<T>(mState);
	}

	void NextPatrolPointIndex()
	{
		mPatrolIndex += mPatrolDir;

		if (mPatrolIndex >= mPatrolPointArray.Num())
		{
			mPatrolDir = -1;

			mPatrolIndex -= 2;
		}

		else if (mPatrolIndex < 0)
		{
			mPatrolDir = 1;

			mPatrolIndex = 1;
		}
	}

	FVector GetPatrolPoint()
	{
		return mPatrolPointArray[mPatrolIndex];
	}

	bool IsPatrolPointEmpty()
	{
		return mPatrolPointArray.IsEmpty();
	}

	auto SetPatrolArray(const TArray<class APatrolPointActor*>& PatrolArray) -> void;

	void SetSpawnPoint(class AAISpawnPoint* Point)
	{
		mSpawnPoint = Point;
	}

	void SetAttackEnd(bool End)
	{
		mAttackEnd = End;
	}

	bool IsAttackEnd()
	{
		return mAttackEnd;
	}
	
	float GetHalfHeight()	const
	{
		return mCapsule->GetScaledCapsuleHalfHeight();
	}

	float GetCapsuleRadius()
	{
		return mCapsule->GetScaledCapsuleRadius();
	}

	virtual void ChangeAIAnimType(uint8 AnimType);

	virtual void OnConstruction(const FTransform& Transform) override;
	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

};
