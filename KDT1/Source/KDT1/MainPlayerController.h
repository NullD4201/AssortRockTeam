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

private:
	float	mMoveDir;

	bool	mDetectEnable = false;
	float	mDetectTime = 0.f;
	float	mDetectDuration = 4.f;
	float	mDetectDelayTime = 0.f;
	float	mDetectDelay = 0.4f;
	TArray<AActor*>	mDetectActorArray;

public:
	float GetMoveDir()
	{
		return mMoveDir;
	}

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnRandomColor(const FInputActionValue& InputActionValue);
	void OnSwordAttack(const FInputActionValue& InputActionValue);
};
