// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/BasicInputDataConfig.h"
#include "Character/MainCharacter.h"

AMainPlayerController::AMainPlayerController()
{

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
	EnhancedInputComponent->BindAction(MainInputDataConfig->RandomColor, ETriggerEvent::Triggered, this, &ThisClass::OnRandomColor);
	EnhancedInputComponent->BindAction(MainInputDataConfig->SwordAttack, ETriggerEvent::Started, this, &ThisClass::OnSwordAttack);
	EnhancedInputComponent->BindAction(MainInputDataConfig->SwordSkill, ETriggerEvent::Started, this, &ThisClass::OnSwordSkill);
}

void AMainPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	// 공격 중이 아닌 경우에만 이동 코드를 실행
	
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

	// 이동 방향을 저장한다.
	// 먼저 ActionValue.X 는 왼쪽일때 -1, 오른쪽일때 1, 좌우로 움직이지 않을경우
	// 0이 들어오게 된다.
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

void AMainPlayerController::OnSwordAttack(const FInputActionValue& InputActionValue)
{
	// 컨트롤하는 캐릭터의 애니메이션을 공격 모션으로 전환한다.
	// 애님인스턴스는 플레이어 캐릭터의 SkeletalMeshComponent에 있으므로
	// PlayerCharacter 를 얻어온다.
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	// PlayAttackMontage에서는 애님인스턴스의 공격 몽타주를 재생시켜준다.
	ControlledPawn->PlayAttackMontage();

	// 공격이 끝나면 bIsAttacking을 다시 false로 설정

	/*GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.5f, FColor::Yellow, TEXT("bIsAttacking  = false"));*/
}

void AMainPlayerController::OnSwordSkill(const FInputActionValue& InputActionValue)
{
	// 컨트롤하는 캐릭터의 애니메이션을 공격 모션으로 전환한다.
	// 애님인스턴스는 플레이어 캐릭터의 SkeletalMeshComponent에 있으므로
	// PlayerCharacter 를 얻어온다.
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	// PlayAttackMontage에서는 애님인스턴스의 공격 몽타주를 재생시켜준다.
	ControlledPawn->PlaySkillMontage(0);

	// 공격이 끝나면 bIsAttacking을 다시 false로 설정

	/*GEngine->AddOnScreenDebugMessage(INDEX_NONE, 0.5f, FColor::Yellow, TEXT("bIsAttacking  = false"));*/
}

void AMainPlayerController::OnRandomColor(const FInputActionValue& InputActionValue)
{	
	
	int a, b, c;
	a = FMath::RandRange(0.0, 255.0);
	b = FMath::RandRange(0.0, 255.0);
	c = FMath::RandRange(0.0, 255.0);
	GEngine->AddOnScreenDebugMessage(INDEX_NONE, 3600.0f, FColor(a, b, c), TEXT("■■■■■■■■■■■■■■"));
}