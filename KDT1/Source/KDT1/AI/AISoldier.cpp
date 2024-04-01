// Fill out your copyright notice in the Description page of Project Settings.


#include "AISoldier.h"

#include "SoldierState.h"
#include "Engine/DamageEvents.h"

AAISoldier::AAISoldier()
{
	PrimaryActorTick.bCanEverTick = true;

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> MeshAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/KoreanTraditionalMartialArts/Meshs/Characters/Meshs/SKM_Soldier_2.SKM_Soldier_2'"));
	if (MeshAsset.Succeeded())
	{
		mMesh->SetSkeletalMesh(MeshAsset.Object);
	}

	static ConstructorHelpers::FClassFinder<UAnimInstance> AnimAsset(TEXT("/Script/Engine.AnimBlueprint'/Game/KoreanTraditionalMartialArts/Animations/Hwando/AB_HwandoSoldier.AB_HwandoSoldier_C'"));
	if (AnimAsset.Succeeded())
	{
		mMesh->SetAnimInstanceClass(AnimAsset.Class);
	}

	static ConstructorHelpers::FObjectFinder<USkeletalMesh> WeaponAsset(TEXT("/Script/Engine.SkeletalMesh'/Game/KoreanTraditionalMartialArts/Meshs/Weapons/Meshs/SKM_Hwando.SKM_Hwando'"));
	if (WeaponAsset.Succeeded())
	{
		mWeaponMesh->SetSkeletalMesh(WeaponAsset.Object);
	}

	mMesh->SetRelativeLocation(FVector(0.0, 0.0, -90.0));
	mMesh->SetRelativeRotation(FRotator(0.0, -90.0, 0.0));

	mCapsule->SetCapsuleHalfHeight(90.f);
	mCapsule->SetCapsuleRadius(30.f);

	mTableRowName = TEXT("SoldierHwando");
}

void AAISoldier::BeginPlay()
{
	Super::BeginPlay();
}

void AAISoldier::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}

void AAISoldier::NormalAttack()
{
	FCollisionQueryParams	param(NAME_None, false, this);

	FVector StartLocation = GetActorLocation() + GetActorForwardVector() + 50.f;
	FVector EndLocation = StartLocation + GetActorForwardVector() + 150.f;

	FHitResult result;
	bool IsCollision = GetWorld()->SweepSingleByChannel(result, StartLocation, EndLocation, FQuat::Identity, ECC_GameTraceChannel7, FCollisionShape::MakeSphere(50.f), param);

#if ENABLE_DRAW_DEBUG

	// 구를 그린다.
	FColor	DrawColor = IsCollision ? FColor::Red : FColor::Green;

	DrawDebugCapsule(GetWorld(), (StartLocation + EndLocation) / 2.f,
		75.f, 50.f, FRotationMatrix::MakeFromZ(GetActorForwardVector()).ToQuat(),
		DrawColor, false, 3.f);

#endif

	if (IsCollision)
	{
		FDamageEvent DmgEvent;
		result.GetActor()->TakeDamage(mSoldierState->mAttackPoint, DmgEvent, GetController(), this);

		FActorSpawnParameters	SpawnParams;
		SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	}
}
