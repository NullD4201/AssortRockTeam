// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "EngineMinimal.h"
#include "Engine.h"
#include "Engine/DamageEvents.h"

#include "BehaviorTree/BehaviorTree.h"
#include "BehaviorTree/BlackboardData.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "KismetAnimationLibrary.h"

#include "UObject/NoExportTypes.h"
#include "GameInfo.generated.h"

DECLARE_LOG_CATEGORY_EXTERN(KDT1, Log, All);


UENUM(BlueprintType)
enum class EPlayerAnimType : uint8
{
	Idle,
	Run,
	Dodge,
	Attack,
	Skill,
	CoolDown,
	Death
};

UENUM(BlueprintType)
enum class EPlayerWeaponType : uint8
{
	Sword,
	Spear,
	Bow
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
