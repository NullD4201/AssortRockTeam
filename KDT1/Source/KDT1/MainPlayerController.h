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
	TSubclassOf<UUserWidget>	mMainWidgetClass;
	UUserWidget* mMainWidget; // 실제생성된 위젯객체의 메모리주소를 저장할 용도의 포인터변수


protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;

protected:
	void OnMove(const FInputActionValue& InputActionValue);
	void OnLook(const FInputActionValue& InputActionValue);
	void OnAttack(const FInputActionValue& InputActionValue);
	void OnSkill(const FInputActionValue& InputActionValue);
	void ChangeToSword(const FInputActionValue& InputActionValue);
	void ChangeToSpear(const FInputActionValue& InputActionValue);
};
