// Fill out your copyright notice in the Description page of Project Settings.


#include "MainGameModeBase.h"
#include "../Character/MainCharacter.h"
#include "../MainPlayerController.h"
#include "KDT1/Character/SpearCharacter.h"
#include "KDT1/Character/SwordCharacter.h"


AMainGameModeBase::AMainGameModeBase()
{
	DefaultPawnClass = ASpearCharacter::StaticClass();
	PlayerControllerClass = AMainPlayerController::StaticClass();

}
