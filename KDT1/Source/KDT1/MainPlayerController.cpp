// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/BasicInputDataConfig.h"
#include "Character/MainCharacter.h"
#include "Character/PlayerAnimInstance.h"
#include "Item/Weapon.h"

AMainPlayerController::AMainPlayerController()
{
	mSpearMesh = LoadObject<USkeletalMesh>(GetWorld(),
		TEXT("/Script/Engine.SkeletalMesh'/Game/SpearAnimation/Demo/Character/Mesh/Weapom_Spear.Weapom_Spear'"));
}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UBasicInputDataConfig* MainInputDataConfig = GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(MainInputDataConfig->DefaultContext, 0);

}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* MainInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Attack, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Item1, ETriggerEvent::Triggered, this, &ThisClass::OnItem1);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeFwd, ETriggerEvent::Triggered , this, &ThisClass::OnDodgeFwd);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeBwd, ETriggerEvent::Triggered , this, &ThisClass::OnDodgeBwd);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeRight, ETriggerEvent::Triggered , this, &ThisClass::OnDodgeRight);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeLeft, ETriggerEvent::Triggered , this, &ThisClass::OnDodgeLeft);
}

void AMainPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector ForwardVector = YawRotation.Vector();
	const FVector RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// 앞 뒤 이동
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	// 좌 우 이동
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);

	/*mMoveDir = ActionValue.X * 90.f;

	if (ActionValue.Y > 0.f)
	{
		if (ActionValue.X < 0.f)
			mMoveDir = -45.f;

		else if (ActionValue.X > 0.f)
			mMoveDir = 45.f;
	}

	else if (ActionValue.Y < 0.f)
	{
		if (ActionValue.X < 0.f)
			mMoveDir = -135.f;

		else if (ActionValue.X > 0.f)
			mMoveDir = 135.f;

		else
			mMoveDir = 180.f;
	}*/
}

void AMainPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	const FVector ActionValue = InputActionValue.Get<FVector>();
	AddYawInput(ActionValue.X);
	AddPitchInput(ActionValue.Y);
}

void AMainPlayerController::OnAttack(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayAttackMontage();
}

void AMainPlayerController::OnItem1(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	if (!ControlledPawn->GetBoolSpearEquip())
	{
		ControlledPawn->SetBoolSpear(true);
		ControlledPawn->SetWeaponMesh(mSpearMesh);
	}
}

void AMainPlayerController::OnDodgeFwd(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledCharacter = GetPawn<AMainCharacter>();
	ControlledCharacter->PlayDodgeMontage(0);
}

void AMainPlayerController::OnDodgeBwd(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledCharacter = GetPawn<AMainCharacter>();
	ControlledCharacter->PlayDodgeMontage(1);
}

void AMainPlayerController::OnDodgeRight(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledCharacter = GetPawn<AMainCharacter>();
	ControlledCharacter->PlayDodgeMontage(2);
}

void AMainPlayerController::OnDodgeLeft(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledCharacter = GetPawn<AMainCharacter>();
	ControlledCharacter->PlayDodgeMontage(3);
}
