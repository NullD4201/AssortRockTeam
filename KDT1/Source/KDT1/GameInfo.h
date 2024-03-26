// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"


UENUM(BlueprintType)
enum class EPlayerType : uint8
{
	Idle,
	Walk,
	Sprint
};


/**
 * 
 */
UCLASS()
class KDT1_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
