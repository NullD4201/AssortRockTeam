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

protected:
	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	UCameraComponent* mCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	USpringArmComponent* mCameraArm;

	class UPlayerAnimInstance* mAnimInst;
	class AWeapon* mWeapon;

	bool bSpearEquip;

	//UPROPERTY(VisibleAnywhere, BlueprintReadWrite)
	//USkeletalMeshComponent* mWeaponMesh;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

public:
	void SetWeaponMesh(USkeletalMesh* WeaponMesh);
	void PlayAttackMontage();
	void PlayDodgeMontage();

	void SetBoolSpear(bool equip)
	{
		bSpearEquip = equip;
	}
	bool GetBoolSpearEquip()
	{
		return bSpearEquip;
	}
};
