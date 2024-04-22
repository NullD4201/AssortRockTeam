// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../Character/MainCharacter.h"
#include "../MainPlayerController.h"
#include "../Character/SpearCharacter.h"
#include "../Character/SwordCharacter.h"


AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}

APlayerController* AMainGameModeBase::Login(UPlayer* NewPlayer, ENetRole InRemoteRole, const FString& Portal, const FString& Options, const FUniqueNetIdRepl& UniqueId, FString& ErrorMessage)
{
	APlayerController* result = Super::Login(NewPlayer, InRemoteRole, Portal,
		Options, UniqueId, ErrorMessage);

	//UE_LOG(KDT1, Warning, TEXT("%s"), *Options);

	int32	CommandType;

	// Options 문자열에 Type=값 이 있다면 찾아서 값을 CommandType에
	// 넣어준다.
	if (FParse::Value(*Options, TEXT("Type="), CommandType))
	{
		EPlayerWeaponType PlayerType = (EPlayerWeaponType)CommandType;

		switch (PlayerType)
		{
		case EPlayerWeaponType::Spear:
			DefaultPawnClass = ASpearCharacter::StaticClass();
			break;
		case EPlayerWeaponType::Sword:
			DefaultPawnClass = ASwordCharacter::StaticClass();
			break;
		}
	}

	return result;
}
