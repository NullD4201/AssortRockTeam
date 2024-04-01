// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "SoldierPawn.h"
#include "AISoldier.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API AAISoldier : public ASoldierPawn
{
	GENERATED_BODY()

public:
	AAISoldier();

protected:
	virtual void BeginPlay() override;

public:
	virtual void Tick(float DeltaSeconds) override;
	virtual void NormalAttack() override;
};
