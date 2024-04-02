// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mIdleMaxSpeed = 600.f;
	mSprintMaxSpeed = 1000.f;
	mIsSprinting = false;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);

	mMesh->SetupAttachment(GetMesh(), "weapon");
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();

	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	mCurrentMaxWalkSpeed = mIdleMaxSpeed;
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	mCurrentSpeed = GetCharacterMovement()->Velocity.Length();
	if (mCurrentSpeed < 10.f)
		mCurrentMaxWalkSpeed = mIdleMaxSpeed;

	if (mIsSprinting == true && mCurrentMaxWalkSpeed < mSprintMaxSpeed && mCurrentSpeed > 10.f)
	{
		mSpeedTime += DeltaTime;

		if (mSpeedTime >= mDuration)
		{
			mSpeedTime = 0.f;
			mCurrentMaxWalkSpeed += 50.f;
		}
	}
	if (mIsSprinting == false && mCurrentMaxWalkSpeed > mIdleMaxSpeed)
	{
		mSpeedTime += DeltaTime;

		if (mSpeedTime >= mDuration)
		{
			mSpeedTime = 0.f;
			mCurrentMaxWalkSpeed -= 50.f;
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = mCurrentMaxWalkSpeed;
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

void AMainCharacter::NormalAttack()
{
	// TODO NormalAttack()
}

void AMainCharacter::PlayAttackMontage()
{
	mAnimInst->PlayAttackMontage();
}

void AMainCharacter::PlaySprint()
{
	mIsSprinting = true;
	mSpeedTime = 0.f;

	mAnimInst->PlaySprint();
}
void AMainCharacter::PlaySprintEnd()
{
	mIsSprinting = false;
	mSpeedTime = 0.f;

	mAnimInst->PlaySprintEnd();
}

void AMainCharacter::PlayDodgeMontage(int8 index)
{
	mAnimInst->PlayDodgeMontage(index);
}

void AMainCharacter::PlaySkillMontage()
{
	mAnimInst->PlaySkillMontage();
}

void AMainCharacter::TargetLock()
{
	mAnimInst->TargetLock();
}

void AMainCharacter::ChangeToWeaponSword()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon1"));
}

void AMainCharacter::ChangeToWeaponSpear()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon2"));
}


