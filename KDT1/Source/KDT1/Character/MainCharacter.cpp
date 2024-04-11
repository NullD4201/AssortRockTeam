// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Kismet/KismetMathLibrary.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mIdleMaxSpeed = 600.f;
	mSprintMaxSpeed = 1000.f;
	mIsSprinting = false;
	mIsTargetLocked = false;
	mIsAngleLocked = false;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	mCheckRadius = CreateDefaultSubobject<USphereComponent>(TEXT("CheckRadius"));

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);

	mCheckRadius->SetupAttachment(GetCapsuleComponent());
	mCheckRadius->SetSphereRadius(3000.f);
	mCheckRadius->SetCollisionProfileName(TEXT("EnemyTrace"));

	mMesh->SetupAttachment(GetMesh(), "weapon");

	mCheckRadius->OnComponentBeginOverlap.AddDynamic(this, &AMainCharacter::OnActiveRadiusBeginOverlap);
	mCheckRadius->OnComponentEndOverlap.AddDynamic(this, &AMainCharacter::OnActiveRadiusEndOverlap);

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

	//GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Green, FString::SanitizeFloat(mTargetArray.Num()));
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
	if (mAnimInst->GetAnimType() == EPlayerAnimType::Dodge || mAnimInst->GetAnimType() == EPlayerAnimType::Attack
		|| mAnimInst->GetAnimType() == EPlayerAnimType::Skill || mAnimInst->GetAnimType() == EPlayerAnimType::CoolDown)
	{
		return;
	}
	// 변화 없음

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
		FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(350.f),
		param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
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

		FRotator ViewRot  = GetControlRotation();

		FRotator PlayerRot = FRotationMatrix::MakeFromX(TargetVec - ActorVec).Rotator();
		//FRotator PlayerFindRot = UKismetMathLibrary::FindLookAtRotation(ActorVec, TargetVec);
		//(MakeFromX 랑 같은 함수)

		//PlayerRot.Pitch = GetController()->K2_GetActorRotation().Pitch;
		//(TargetLock 된 상태에서 마우스 Pitch 값만 사용하는 기능 /
		// MainController에서 Input 안들어오게 설정해놔서 지금은 의미없음)

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
	// 지금 Target Lock 된 Actor 가 아닐 경우 실행
	// Closest Right AI 변수 하나 만들어놓고 한번 초기화 시켜주고
	// 반복문을 돌면서 , (mTargetArray .Num 만큼)
	// Target이랑 Array AI 랑 Actor Right Vec 이랑 내적 값 잡아서
	// RIght 가져오고, 그 중에서 값 비교해서 가장 오른쪽 AI 변수에 넣어주고
	// Target 변경 해주기

	if (!mIsTargetLocked)
		return;

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

	// LeftArray 배열 중에서 가장 Target과 가까운 놈 찾아내기
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

	// LeftArray 배열 중에서 가장 Target과 가까운 놈 찾아내기
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

void AMainCharacter::CheckDotValueInRadius(float DeltaTime)
{
	FCollisionQueryParams	param(NAME_None, false, this);

	FVector StartLocation = GetActorLocation();
	FVector EndLocation = GetActorLocation() + 1.f;

	FHitResult	result;

	bool IsCollision = GetWorld()->SweepSingleByChannel(result, StartLocation, EndLocation,
		FQuat::Identity, ECC_GameTraceChannel2, FCollisionShape::MakeSphere(1000.f),
		param);

	if (IsCollision)
	{
		FVector CameraForwardVec = mCamera->GetForwardVector();
		FVector ToTargetVec = result.GetActor()->GetActorLocation() - GetActorLocation();
		ToTargetVec.Normalize();

		FVector TargetVec = ToTargetVec - GetActorForwardVector();
		TargetVec.Normalize();

		float DotValue = FVector::DotProduct(CameraForwardVec, TargetVec);

		GEngine->AddOnScreenDebugMessage(-1, 1.f, FColor::Blue, FString::SanitizeFloat(DotValue));

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


