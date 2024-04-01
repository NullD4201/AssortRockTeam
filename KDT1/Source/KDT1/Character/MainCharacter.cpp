// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mIdleMaxSpeed = 600.f;
	mSprintMaxSpeed = 1000.f;

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

	FOnTimelineFloat ProgressUpdate;
	ProgressUpdate.BindUFunction(this, FName("PlayerSpeedUpdate"));
	FOnTimelineEvent FinishedEvent;
	FinishedEvent.BindUFunction(this, FName("PlayerSpeedFinished"));

	PlayerSpeedTimeline.AddInterpFloat(PlayerSpeedCurve, ProgressUpdate);
	PlayerSpeedTimeline.SetTimelineFinishedFunc(FinishedEvent);
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	PlayerSpeedTimeline.TickTimeline(DeltaTime);
}

void AMainCharacter::PlayerSpeedUpdate(float Alpha)
{
	float NewPlayerSpeed = FMath::Lerp(mIdleMaxSpeed, mSprintMaxSpeed, Alpha);
	GetCharacterMovement()->MaxWalkSpeed = NewPlayerSpeed;
}

void AMainCharacter::PlayerSpeedFinished()
{
}

void AMainCharacter::StartSprinting()
{
	PlayerSpeedTimeline.Play();
}

void AMainCharacter::StopSprinting()
{
	PlayerSpeedTimeline.Reverse();
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
	mAnimInst->PlaySprint();
}
void AMainCharacter::PlaySprintEnd()
{
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


