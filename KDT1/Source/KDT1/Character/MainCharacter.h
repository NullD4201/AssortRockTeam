// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "KDT1/UI/PlayerHUDWidget.h"
#include "MainCharacter.generated.h"


UCLASS()
class KDT1_API AMainCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AMainCharacter();
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mPlayerEyeSightCamera;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	EPlayerWeaponType	mPlayerWeaponType;

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	int32	mAttackPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32	mArmorPoint;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32	mHp;
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32	mHpMax;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mPlayerEyeSightCameraArm;

	class UPlayerAnimInstance* mAnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* mCheckRadius = nullptr;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mEyeSightCameraArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* mPlayerEyeSight;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UPlayerHUDWidget*	mPlayerHUDWidget;

	float mIdleMaxSpeed;
	float mSprintMaxSpeed;
	float mCurrentMaxWalkSpeed;
	bool  mIsSprinting;
	float mCurrentSpeed;
	bool mIsTargetLocked;
	bool mIsAngleLocked;
	float FixedZValue = 2800.f;
	float FixedPitchValue = 90.f;
	float FixedYawValue = 90.f;

	AActor* TargetActor = nullptr;
	TArray<AActor*>	mTargetArray;
	TArray<AActor*> mRightAIArray;
	TArray<AActor*> mLeftAIArray;
	AActor* ClosestRightAI = nullptr;
	AActor* ClosestLeftAI = nullptr;

	float mSpeedTime = 0.f;
	float mDuration = 0.1f;

	void PlayerWalkSpeedUpSmoothly(float DeltaTime);
	void PlayerTargetLocked(float DeltaTime);
	void CheckPlayerCameraAngle();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void NormalAttack();

	void PlayAttackMontage();
	void PlaySprint();
	void PlaySprintEnd();
	void PlayDodgeMontage(int8 index);
	void PlaySkillMontage();
	void TargetLock();
	void SwitchLeft();
	void SwitchRight();

	bool GetboolTargetLocked()
	{
		return mIsTargetLocked;
	}

	UFUNCTION()
	void OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void ChangeToWeaponSword();
	void ChangeToWeaponSpear();

private:
	class UAIPerceptionStimuliSourceComponent* StimulusSource;

	void SetupStimulusSource();

};