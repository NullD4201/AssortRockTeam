// Fill out your copyright notice in the Description page of Project Settings.


#include "MainCharacter.h"
#include "PlayerAnimInstance.h"
#include "../Item/Weapon.h"

// Sets default values
AMainCharacter::AMainCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mCameraArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraArm"));
	mCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));

	mCameraArm->SetupAttachment(GetCapsuleComponent());
	mCamera->SetupAttachment(mCameraArm);

	//mWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	//mWeaponMesh->SetupAttachment(GetMesh());
}

// Called when the game starts or when spawned
void AMainCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	mAnimInst = Cast<UPlayerAnimInstance>(GetMesh()->GetAnimInstance());

	bSpearEquip = false;

	/*USkeletalMeshComponent* mMesh;
	static ConstructorHelpers::FObjectFinder<USkeletalMeshComponent> Asset(TEXT("/Script/Engine.SkeletalMesh'/Game/SpearAnimation/Demo/Character/Mesh/Weapom_Spear.Weapom_Spear'"));
	if (Asset.Succeeded())
		mMesh = Asset.Object;*/

	FActorSpawnParameters	param;
	param.SpawnCollisionHandlingOverride =
		ESpawnActorCollisionHandlingMethod::AlwaysSpawn;
	mWeapon = GetWorld()->SpawnActor<AWeapon>(
		FVector::ZeroVector, FRotator::ZeroRotator,
		param);
	mWeapon->AttachToComponent(GetMesh(),
		FAttachmentTransformRules::KeepRelativeTransform,
		TEXT("Weapon_Spear"));

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

void AMainCharacter::SetWeaponMesh(USkeletalMesh* WeaponMesh)
{
	mWeapon->SetMesh(WeaponMesh);
}

void AMainCharacter::PlayAttackMontage()
{
	if(bSpearEquip)
		mAnimInst->PlayAttackMontage();
}

