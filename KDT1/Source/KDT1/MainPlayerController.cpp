// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/BasicInputDataConfig.h"
#include "Character/MainCharacter.h"
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

	mMoveDir = ActionValue.X * 90.f;

	// ActionValue.Y는 앞일때 1, 뒤일때 -1, 앞뒤로 움직이지 않을 경우 0이다.
	// 앞으로 이동할 경우
	if (ActionValue.Y > 0.f)
	{
		// 앞으로 이동하는데 왼쪽으로 이동하고 있을 경우
		// 왼쪽 전방 대각선 이동이다.
		if (ActionValue.X < 0.f)
			mMoveDir = -45.f;

		// 앞으로 이동하는데 오른쪽으로 이동하고 있을 경우
		// 오른쪽 전방 대각선 이동이다.
		else if (ActionValue.X > 0.f)
			mMoveDir = 45.f;
	}

	// 뒤로 이동할 경우
	else if (ActionValue.Y < 0.f)
	{
		// 뒤로 이동하는데 왼쪽으로 이동하고 있을 경우
		// 왼쪽 후방 대각선 이동이다.
		if (ActionValue.X < 0.f)
			mMoveDir = -135.f;

		// 뒤로 이동하는데 오른쪽으로 이동하고 있을 경우
		// 오른쪽 후방 대각선 이동이다.
		else if (ActionValue.X > 0.f)
			mMoveDir = 135.f;

		// 뒤로 이동할 경우
		else
			mMoveDir = 180.f;
	}
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
