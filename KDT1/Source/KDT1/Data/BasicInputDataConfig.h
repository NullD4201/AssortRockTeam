// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputMappingContext.h"
#include "InputAction.h"
#include "BasicInputDataConfig.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API UBasicInputDataConfig : public UObject
{
	GENERATED_BODY()
	
public:
	UBasicInputDataConfig();

public:
	//UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input)
	UInputMappingContext* DefaultContext = nullptr;

public:
	UInputAction* Move = nullptr;
	UInputAction* Look = nullptr;
	UInputAction* Attack = nullptr;
	UInputAction* Item1 = nullptr;
	UInputAction* DodgeFwd = nullptr;
	UInputAction* DodgeBwd = nullptr;
	UInputAction* DodgeRight = nullptr;
	UInputAction* DodgeLeft = nullptr;

};
