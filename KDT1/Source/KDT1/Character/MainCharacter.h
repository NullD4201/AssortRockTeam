// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	class UPlayerAnimInstance* mAnimInst;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USkeletalMeshComponent* mMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	USphereComponent* mCheckRadius = nullptr;

	float mIdleMaxSpeed;
	float mSprintMaxSpeed;
	float mCurrentMaxWalkSpeed;
	bool  mIsSprinting;
	float mCurrentSpeed;
	bool mIsTargetLocked;
	bool mIsAngleLocked;

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