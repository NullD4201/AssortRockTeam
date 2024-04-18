// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"
#include "Perception/AIPerceptionStimuliSourceComponent.h"
#include "Perception/AISenseConfig_Sight.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAttackPoint = 50;
	mArmorPoint = 15;
	mHpMax = 500;
	mHp = mHpMax;

	mIdleMaxSpeed = 600.f;
	mSprintMaxSpeed = 1000.f;
	mIsSprinting = false;
	mIsTargetLocked = false;
	mIsAngleLocked = false;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	mCheckRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CheckRadius"));
	/*mEyeSightCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("EyeSightCameraArm"));
	mEyeSightCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("EyeSightCamera"));*/
	mPlayerEyeSight = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("PlayerEyeSight"));

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);
	mPlayerEyeSight->SetupAttachment(GetRootComponent());

	mCheckRadius->SetupAttachment(GetCapsuleComponent());
	mCheckRadius->SetSphereRadius(3000.f);
	mCheckRadius->SetCollisionProfileName(TEXT("EnemyTrace"));

	mMesh->SetupAttachment(GetMesh(), "weapon");

	mCheckRadius->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnActiveRadiusBeginOverlap);
	mCheckRadius->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnActiveRadiusEndOverlap);

	GetCapsuleComponent()->SetCollisionProfileName(TEXT("Player"));

	SetupStimulusSource();
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

	PlayerWalkSpeedUpSmoothly(DeltaTime);

	PlayerTargetLocked(DeltaTime);

	FRotator Camera_CurrentRotation = mCamera->GetComponentRotation();
	mPlayerEyeSight->SetRelativeRotation(FRotator(90.f,Camera_CurrentRotation.Yaw, Camera_CurrentRotation.Roll), false);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

float AMainCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	GEngine->AddOnScreenDebugMessage(-1, 1, FColor::Green, TEXT("Player TakeDamage " + FString::FromInt(DamageAmount - mArmorPoint)));

	return DamageAmount;
}

void AMainCharacter::NormalAttack()
{
	FCollisionQueryParams	param(NAME_None, false, this);
	
	FVector StartLocation = GetActorLocation();
	FVector EndLocation = StartLocation + GetActorForwardVector() * 50;
	TArray<FHitResult> resultArray;
	bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel6, FCollisionShape::MakeSphere(50.f), param);

#if ENABLE_DRAW_DEBUG
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;
	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		50 / 2.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 3.f);
#endif

	if (IsCollision)
	{
		for (int32 i = 0; i < resultArray.Num(); ++i)
		{
			FDamageEvent	DmgEvent;
			resultArray[i].GetActor()->TakeDamage(mAttackPoint, DmgEvent, GetController(), this);
		}
	}
}

void AMainCharacter::PlayAttackMontage()
{
	mAnimInst->PlayAttackMontage();
}

void AMainCharacter::PlaySprint()
{
	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill || mAnimInst->GetAnimType() == EPlayerAnimType::CoolDown)
	{
		return;
	}

	mIsSprinting = true;
	mSpeedTime = 0.f;

	mAnimInst->PlaySprint();
}
void AMainCharacter::PlaySprintEnd()
{
	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill || mAnimInst->GetAnimType() == EPlayerAnimType::CoolDown)
	{
		return;
	}

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

void AMainCharacter::PlayerWalkSpeedUpSmoothly(float DeltaTime)
{
	mCurrentSpeed = GetCharacterMovement()->Velocity.Length();

	if (mCurrentSpeed < 10.f)
		mCurrentMaxWalkSpeed = mIdleMaxSpeed;

	if (mIsSprinting == true && mCurrentMaxWalkSpeed < mSprintMaxSpeed && mCurrentSpeed > 10.f)
	{
		mSpeedTime += DeltaTime;

		if (mSpeedTime >= mDuration)
		{
			mSpeedTime = 0.f;
			mCurrentMaxWalkSpeed += 100.f;
		}
	}
	if (mIsSprinting == false && mCurrentMaxWalkSpeed > mIdleMaxSpeed)
	{
		mSpeedTime += DeltaTime;

		if (mSpeedTime >= mDuration)
		{
			mSpeedTime = 0.f;
			mCurrentMaxWalkSpeed -= 100.f;
		}
	}
	GetCharacterMovement()->MaxWalkSpeed = mCurrentMaxWalkSpeed;
}

void AMainCharacter::TargetLock()
{
	if (mIsTargetLocked)
	{
		mIsTargetLocked = false;
		mIsAngleLocked = false;

		mAnimInst->TargetLock();

		return;
	}

	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill)
		return;

	FCollisionQueryParams	param(NAME_None, false, this);

	FVector StartLocation = GetActorLocation() + mCamera->GetForwardVector() * 350.f;
	FVector EndLocation = StartLocation + mCamera->GetForwardVector() * 1000.f;

	FHitResult	result;

	bool IsCollision = GetWorld()->SweepSingleByChannel(result, StartLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel1, FCollisionShape::MakeSphere(350.f),
		param);

#if ENABLE_DRAW_DEBUG

	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		1000.f, 350.f, FRotationMatrix::MakeFromZ(mCamera->GetForwardVector()).ToQuat(),
		DrawColor, false, 3.f);

#endif
	if (IsCollision)
	{
		TargetActor = result.GetActor();

		mIsTargetLocked = true;

		mAnimInst->TargetLock();
	}
}

void AMainCharacter::PlayerTargetLocked(float DeltaTime)
{
	if (mIsTargetLocked)
	{
		FVector  TargetVec = TargetActor->GetActorLocation();
		FVector  ActorVec = GetActorLocation();

		FRotator ViewRot = GetControlRotation();

		FRotator PlayerRot = FRotationMatrix::MakeFromX(TargetVec - ActorVec).Rotator();

		FRotator RInter = FMath::RInterpTo(ViewRot, PlayerRot, DeltaTime, 5.f);

		GetController()->SetControlRotation(RInter);

		CheckPlayerCameraAngle();
	}
	else
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = false;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AMainCharacter::CheckPlayerCameraAngle()
{
	if (mIsAngleLocked)
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
		return;
	}
	FVector CameraForwardVec = mCamera->GetForwardVector();

	FVector ToTargetVec = TargetActor->GetActorLocation() - GetActorLocation();
	ToTargetVec.Normalize();

	FVector TargetVec = ToTargetVec - GetActorForwardVector();
	TargetVec.Normalize();

	float DotValue = FVector::DotProduct(CameraForwardVec, TargetVec);

	if (DotValue >= -0.1f && DotValue <= 0.3f)
	{
		mIsAngleLocked = true;
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = false;
	}
	else
	{
		GetCharacterMovement()->bUseControllerDesiredRotation = true;
		GetCharacterMovement()->bOrientRotationToMovement = true;
	}
}

void AMainCharacter::SwitchLeft()
{
	if (!mIsTargetLocked)
		return;

	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill || mAnimInst->GetAnimType() == EPlayerAnimType::CoolDown)
	{
		return;
	}

	ClosestLeftAI = nullptr;
	mLeftAIArray.Reset();

	for (int32 i = 0; i < mTargetArray.Num(); ++i)
	{
		if (mTargetArray[i] != TargetActor)
		{
			FVector ToTargetVec = TargetActor->GetActorLocation() - mTargetArray[i]->GetActorLocation();
			ToTargetVec.Normalize();

			FVector CameraRightVec = mCamera->GetRightVector();

			float DotValue = FVector::DotProduct(ToTargetVec, CameraRightVec);

			if (DotValue >= 0)
			{
				mLeftAIArray.Add(mTargetArray[i]);
			}
		}
	}

	if (mLeftAIArray.Num() > 0)
		ClosestLeftAI = mLeftAIArray[0];

	for (int32 i = 0; i < mLeftAIArray.Num(); ++i)
	{
		float NewAIDistance = FVector::Distance(TargetActor->GetActorLocation(), mLeftAIArray[i]->GetActorLocation());
		float CloseTargetDis = FVector::Distance(TargetActor->GetActorLocation(), ClosestLeftAI->GetActorLocation());

		if (NewAIDistance < CloseTargetDis)
		{
			ClosestLeftAI = mLeftAIArray[i];
		}
	}

	if (ClosestLeftAI)
	{
		TargetActor = ClosestLeftAI;
	}
}

void AMainCharacter::SwitchRight()
{
	if (!mIsTargetLocked)
		return;

	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill || mAnimInst->GetAnimType() == EPlayerAnimType::CoolDown)
	{
		return;
	}

	ClosestRightAI = nullptr;
	mRightAIArray.Reset();

	for (int32 i = 0; i < mTargetArray.Num(); ++i)
	{
		if (mTargetArray[i] != TargetActor)
		{
			FVector ToTargetVec = TargetActor->GetActorLocation() - mTargetArray[i]->GetActorLocation();
			ToTargetVec.Normalize();

			FVector CameraRightVec = mCamera->GetRightVector();

			float DotValue = FVector::DotProduct(ToTargetVec, CameraRightVec);
			if (DotValue < 0)
			{
				mRightAIArray.Add(mTargetArray[i]);
			}
		}
	}

	if (mRightAIArray.Num() > 0)
		ClosestRightAI = mRightAIArray[0];

	for (int32 i = 0; i < mRightAIArray.Num(); ++i)
	{
		float NewAIDistance = FVector::Distance(TargetActor->GetActorLocation(), mRightAIArray[i]->GetActorLocation());
		float CloseTargetDis = FVector::Distance(TargetActor->GetActorLocation(), ClosestRightAI->GetActorLocation());

		if (NewAIDistance < CloseTargetDis)
		{
			ClosestRightAI = mRightAIArray[i];
		}
	}

	if (ClosestRightAI)
	{
		TargetActor = ClosestRightAI;
	}
}

void AMainCharacter::OnActiveRadiusBeginOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	mTargetArray.Add(Other);
}

void AMainCharacter::OnActiveRadiusEndOverlap(UPrimitiveComponent* OverlappedComp, AActor* Other, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	mTargetArray.Remove(Other);
}

void AMainCharacter::ChangeToWeaponSword()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon1"));
}

void AMainCharacter::ChangeToWeaponSpear()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon2"));
}

void AMainCharacter::SetupStimulusSource()
{
	StimulusSource = CreateDefaultSubobject<UAIPerceptionStimuliSourceComponent>(TEXT("Stimulus"));
	if (StimulusSource)
	{
		StimulusSource->RegisterForSense(TSubclassOf<UAISense_Sight>());
		StimulusSource->RegisterWithPerceptionSystem();
	}
}



