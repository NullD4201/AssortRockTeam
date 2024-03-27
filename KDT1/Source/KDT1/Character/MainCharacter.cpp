// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);
<<<<<<< HEAD
=======

	mMesh->SetupAttachment(GetMesh(), "weapon");
>>>>>>> cdaf7b7 (Add ChangeWeapon Inputs)
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());
}

// Called every frame
void AMainCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AMainCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AMainCharacter::PlayAttackMontage()
{
	mAnimInst->PlayAttackMontage();
}

void AMainCharacter::PlaySkillMontage(int32 Index)
{
	mAnimInst->PlaySkillMontage(Index);
}

void AMainCharacter::NormalAttack()
{
//	FCollisionQueryParams	param(NAME_None, false, this);
//
//	AKDT1PlayerState* State = GetPlayerState<AKDT1PlayerState>();
//
//	FVector	StartLocation = GetActorLocation();
//
//	FVector	EndLocation = StartLocation + GetActorForwardVector() * State->mAttackDistance;
//
//	TArray<FHitResult>	resultArray;
//	bool IsCollision = GetWorld()->SweepMultiByChannel(resultArray,
//		StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel6,
//		FCollisionShape::MakeSphere(50.f), param);
//
//#if ENABLE_DRAW_DEBUG
//
//	// 구를 그린다.
//	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;
//
//	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
//		State->mAttackDistance / 2.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
//		DrawColor, false, 3.f);
//
//#endif
//
//	if (IsCollision)
//	{
//		for (int32 i = 0; i < resultArray.Num(); ++i)
//		{
//			FDamageEvent	DmgEvent;
//
//			resultArray[i].GetActor()->TakeDamage(State->mAttackPoint, DmgEvent,
//				GetController(), this);
//
//			// 이펙트 출력 및 사운드 재생.
//			FActorSpawnParameters	SpawnParam;
//
//			SpawnParam.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
//
//			AEffectBase* Effect = GetWorld()->SpawnActor<AEffectBase>(
//				resultArray[i].ImpactPoint,
//				resultArray[i].ImpactNormal.Rotation(), SpawnParam);
//
//			Effect->SetParticleAsset(TEXT("/Script/Engine.ParticleSystem'/Game/ParagonMinions/FX/Particles/Minions/Minion_melee/FX/Impacts/P_Minion_Impact_Default.P_Minion_Impact_Default'"));
//			Effect->SetSoundAsset(TEXT("/Script/Engine.SoundWave'/Game/ParagonKwang/Characters/Heroes/Kwang/Sounds/SoundWaves/Kwang_Effort_Swing_01.Kwang_Effort_Swing_01'"));
//		}
//	}
}
<<<<<<< HEAD
=======

void AMainCharacter::ChangeToWeaponSword()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon1"));
}

void AMainCharacter::ChangeToWeaponSpear()
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Green, TEXT("Weapon2"));
}


>>>>>>> cdaf7b7 (Add ChangeWeapon Inputs)
