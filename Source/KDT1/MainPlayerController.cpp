// Fill out your copyright notice in the Description page of Project Settings.


#include "MainPlayerController.h"
#include "EnhancedInputSubsystems.h"
#include "EnhancedInputComponent.h"
#include "Data/BasicInputDataConfig.h"
#include "Character/MainCharacter.h"
#include "Blueprint/UserWidget.h"

AMainPlayerController::AMainPlayerController()
{
	static ConstructorHelpers::FClassFinder<UUserWidget>
		MainWidgetClass(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Main/UI/PlayerHUD.PlayerHUD_C'"));

	if (MainWidgetClass.Succeeded()) // 성공했따면
		mMainWidgetClass = MainWidgetClass.Class; // 클래스정보를 저장한다.

}

void AMainPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer());
	const UBasicInputDataConfig* MainInputDataConfig = GetDefault<UBasicInputDataConfig>();
	Subsystem->AddMappingContext(MainInputDataConfig->DefaultContext, 0);

	// 위젯을 생성한다.

	// 생성한 위젯을 이 메인위젯 포인터에 저장
	mMainWidget = CreateWidget<UUserWidget>(GetWorld(), mMainWidgetClass);
	// 인자가 int32 타입으로 ZOrder z순서로 고를수있음 [겹쳐지는거] 여기선 화면에 꽉차게 그려내갰다는말
	mMainWidget->AddToViewport();


}

void AMainPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	ensure(EnhancedInputComponent);

	const UBasicInputDataConfig* MainInputDataConfig = GetDefault<UBasicInputDataConfig>();
	EnhancedInputComponent->BindAction(MainInputDataConfig->Move, ETriggerEvent::Triggered, this, &ThisClass::OnMove);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Look, ETriggerEvent::Triggered, this, &ThisClass::OnLook);
<<<<<<< Updated upstream
	EnhancedInputComponent->BindAction(MainInputDataConfig->Attack, ETriggerEvent::Completed, this, &ThisClass::OnAttack);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill, ETriggerEvent::Completed, this, &ThisClass::OnSkill);
=======
	EnhancedInputComponent->BindAction(MainInputDataConfig->Sprint, ETriggerEvent::Started, this, &ThisClass::OnSprint);
	EnhancedInputComponent->BindAction(MainInputDataConfig->SprintEnd, ETriggerEvent::Triggered, this, &ThisClass::OnSprintEnd);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Attack, ETriggerEvent::Triggered, this, &ThisClass::OnAttack);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Skill, ETriggerEvent::Triggered, this, &ThisClass::OnSkill);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Weapon1, ETriggerEvent::Completed, this, &ThisClass::ChangeToSword);
	EnhancedInputComponent->BindAction(MainInputDataConfig->Weapon2, ETriggerEvent::Completed, this, &ThisClass::ChangeToSpear);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeFwd, ETriggerEvent::Triggered, this, &ThisClass::DodgeFwd);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeBwd, ETriggerEvent::Triggered, this, &ThisClass::DodgeBwd);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeRight, ETriggerEvent::Triggered, this, &ThisClass::DodgeRight);
	EnhancedInputComponent->BindAction(MainInputDataConfig->DodgeLeft, ETriggerEvent::Triggered, this, &ThisClass::DodgeLeft);
	EnhancedInputComponent->BindAction(MainInputDataConfig->TargetLock, ETriggerEvent::Started, this, &ThisClass::OnTargetLock);
>>>>>>> Stashed changes
}

void AMainPlayerController::OnMove(const FInputActionValue& InputActionValue)
{
	APawn* ControlledPawn = GetPawn();

	const FRotator Rotation = K2_GetActorRotation();
	const FRotator YawRotation = FRotator(0.0, Rotation.Yaw, 0.0);
	const FVector  ForwardVector = YawRotation.Vector();
	const FVector  RightVector = FRotationMatrix(YawRotation).GetScaledAxis(EAxis::Y);

	// 앞 뒤 이동
	const FVector ActionValue = InputActionValue.Get<FVector>();
	ControlledPawn->AddMovementInput(ForwardVector, ActionValue.Y);
	// 좌 우 이동
	ControlledPawn->AddMovementInput(RightVector, ActionValue.X);
}

void AMainPlayerController::OnLook(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();
	const FVector ActionValue = InputActionValue.Get<FVector>();

	if (!ControlledPawn->GetboolTargetLocked())
	{
		AddYawInput(ActionValue.X);
		AddPitchInput(ActionValue.Y);

	}
}

void AMainPlayerController::OnSprint(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlaySprint();
}

void AMainPlayerController::OnSprintEnd(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();
	ControlledPawn->PlaySprintEnd();
}

void AMainPlayerController::OnAttack(const FInputActionValue& InputActionValue)
{
	// GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Red, TEXT("Attack"));
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayAttackMontage();
}

void AMainPlayerController::OnSkill(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlaySkillMontage();
}
<<<<<<< Updated upstream
=======

void AMainPlayerController::ChangeToSword(const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Blue, TEXT("Change1"));
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->ChangeToWeaponSword();
}

void AMainPlayerController::ChangeToSpear(const FInputActionValue& InputActionValue)
{
	GEngine->AddOnScreenDebugMessage(-1, 1., FColor::Blue, TEXT("Change2"));
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->ChangeToWeaponSpear();
}

void AMainPlayerController::DodgeFwd(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayDodgeMontage(0);
}

void AMainPlayerController::DodgeBwd(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayDodgeMontage(1);
}

void AMainPlayerController::DodgeRight(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayDodgeMontage(2);
}

void AMainPlayerController::DodgeLeft(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->PlayDodgeMontage(3);
}

void AMainPlayerController::OnTargetLock(const FInputActionValue& InputActionValue)
{
	AMainCharacter* ControlledPawn = GetPawn<AMainCharacter>();

	ControlledPawn->TargetLock();
}
>>>>>>> Stashed changes
