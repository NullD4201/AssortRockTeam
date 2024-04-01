// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Character.h"
#include "Components/TimelineComponent.h"
#include "MainCharacter.generated.h"

class UCurveFloat;

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

	FTimeline PlayerSpeedTimeline;

	UFUNCTION()
	void PlayerSpeedUpdate(float Alpha);
	UFUNCTION()
	void PlayerSpeedFinished();

	float mIdleMaxSpeed;
	float mSprintMaxSpeed;
	
public :
	UPROPERTY(BlueprintReadWrite, EditAnywhere, Category = "TimeLine")
	UCurveFloat* PlayerSpeedCurve = nullptr;

	void StartSprinting();
	void StopSprinting();

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

	void ChangeToWeaponSword();
	void ChangeToWeaponSpear();

};