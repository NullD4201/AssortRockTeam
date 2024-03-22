// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerAnimInstance.h"
#include "MainCharacter.h"

void UPlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

// 이 함수는 매 프레임마다 동작한다.
void UPlayerAnimInstance::NativeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeUpdateAnimation(DeltaSeconds);

	// TryGetPawnOwner() : 이 애니메이션 블루프린트를 사용하고 있는 Pawn 객체를 얻어온다.
	// Cast를 이용하여 AMainCharacter 클래스로 형변환하여 받아온다.
	AMainCharacter* OwnerPawn = Cast<AMainCharacter>(TryGetPawnOwner());

	// IsValid : 객체가 유효한지 체크한다.
	if (IsValid(OwnerPawn))
	{
		UCharacterMovementComponent* Movement = OwnerPawn->GetCharacterMovement();

		if (IsValid(Movement))
		{
			// 속도 벡터의 크기를 구해서 이동속도로 사용한다.
			mMoveSpeed = Movement->Velocity.Length();

			// 속도의 비율을 구한다.
			mMoveSpeed /= Movement->MaxWalkSpeed;
		}
	}

	/*static ConstructorHelpers::FObjectFinder<UAnimMontage>ATTACK_MONTAGE
	(TEXT("/Script/Engine.AnimMontage'/Game/SwordBasicAnimation/SwordPlayer/Attack/AM_SwordAttack.AM_SwordAttack'"));

	if (ATTACK_MONTAGE.Succeeded())
		AttackMontage = ATTACK_MONTAGE.Object;*/
}

void UPlayerAnimInstance::PlayAttackMontage()
{
	Montage_Play(AttackMontage, 1.0f);
}

void UPlayerAnimInstance::JumpToAttackMontageSection(int32 NewSection)
{
	Montage_JumpToSection(GetAttackMontageSectionName(NewSection), AttackMontage);
}

void UPlayerAnimInstance::AnimNotify_AttackHitCheck()
{
	//Broadcast = 델리게이트 안에 있는 모든 함수 실행
	OnAttackHitCheck.Broadcast();
}

void UPlayerAnimInstance::AnimNotify_NextAttackCheck()
{
	OnNextAttackCheck.Broadcast();
}

FName UPlayerAnimInstance::GetAttackMontageSectionName(int32 Section)
{
	return FName(*FString::Printf(TEXT("Attack%d"), Section));
}


