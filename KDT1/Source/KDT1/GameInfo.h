// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(KDT1, Log, All);


UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Idle,
	Walk,
	Run,
	Death,
	Dodge,
	Attack,
	Skill
};

UENUM(BlueprintType)
enum class EPlayerWeaponType : uint8
{
	Sword,
	Spear
};

UENUM(BlueprintType)
enum class ESoldierType : uint8
{
	Hwando,		// 환도
	Woldo		// 월도
};

UCLASS()
class KDT1_API UGameInfo : public UObject
{
	GENERATED_BODY()
	
};
