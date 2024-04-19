// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../Character/MainCharacter.h"
#include "../MainPlayerController.h"


AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = AMainCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();
}
