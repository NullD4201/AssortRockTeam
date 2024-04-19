// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "GameInfo.h"
#include "GameFramework/PlayerController.h"
#include "InputActionValue.h"
#include "MainPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API AMainPlayerController : public APlayerController
{
	GENERATED_BODY()

public :
	AMainPlayerController();
	UUserWidget*		mPlayerHUD;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

	UPROPERTY(EditAnywhere)
	class UPlayerHUDWidget*		UI_PlayerHUD;

	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnSprint(const FInputActionValue& InputActionValue);
	void OnSprintEnd(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnSkill(const FInputActionValue& InputActionValue);
	void ChangeToSword(const FInputActionValue& InputActionValue);
	void ChangeToSpear(const FInputActionValue& InputActionValue);
	void DodgeFwd(const FInputActionValue& InputActionValue);
	void DodgeBwd(const FInputActionValue& InputActionValue);
	void DodgeRight(const FInputActionValue& InputActionValue);
	void DodgeLeft(const FInputActionValue& InputActionValue);
	void OnTargetLock(const FInputActionValue& InputActionValue);
	void OnSwitchLeft(const FInputActionValue& InputActionValue);
	void OnSwitchRight(const FInputActionValue& InputActionValue);
	void OnCharacterChange1(const FInputActionValue& InputActionValue);
	void OnCharacterChange2(const FInputActionValue& InputActionValue);
};
