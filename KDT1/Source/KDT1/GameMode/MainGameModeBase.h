// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/GameModeBase.h"
#include "MainGameModeBase.generated.h"

/**
 * 
 */
UCLASS()
class KDT1_API AMainGameModeBase : public AGameModeBase
{
	GENERATED_BODY()
	
public :
	AMainGameModeBase();

	virtual APlayerController* Login(UPlayer* NewPlayer, ENetRole InRemoteRole,
		const FString& Portal, const FString& Options,
		const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage);

private:
	EPlayerWeaponType	mPlayerWeaponType;

};
