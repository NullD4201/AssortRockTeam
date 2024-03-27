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

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	float mMoveDir;
	USkeletalMesh* mSpearMesh;

public :
	float GetMoveDir()
	{
		return mMoveDir;
	}

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnItem1(const FInputActionValue& InputActionValue);
	void OnDodgeFwd(const FInputActionValue& InputActionValue);
	void OnDodgeBwd(const FInputActionValue& InputActionValue);
	void OnDodgeRight(const FInputActionValue& InputActionValue);
	void OnDodgeLeft(const FInputActionValue& InputActionValue);
};
