// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MainCharacter.generated.h"


UCLASS()
class KDT1_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	class UPlayerAnimInstance* mAnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* mMesh;

	float mIdleMaxSpeed;
	float mSprintMaxSpeed;
	float mCurrentMaxWalkSpeed;
	bool  mIsSprinting;
	float mCurrentSpeed;
	bool mIsTargetLocked;
	AActor* TargetActor = nullptr;

	float mSpeedTime = 0.f;
	float mDuration = 0.1f;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void NormalAttack();

	void PlayAttackMontage();
	void PlaySprint();
	void PlaySprintEnd();
	void PlayDodgeMontage(int8 index);
	void PlaySkillMontage();
	void TargetLock();
	bool GetboolTargetLocked()
	{
		return mIsTargetLocked;
	}

	void ChangeToWeaponSword();
	void ChangeToWeaponSpear();

};