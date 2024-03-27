// Fill out your copyright notice in the Description page of Project Settings.


#include "BasicInputDataConfig.h"

UBasicInputDataConfig::UBasicInputDataConfig()
{
	{
		static ConstructorHelpers::FObjectFinder<UInputMappingContext> Asset
		{ TEXT("/Script/EnhancedInput.InputMappingContext'/Game/Main/Input/IMC_Main.IMC_Main'") };
		if (Asset.Succeeded())
		{
			DefaultContext = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Move.IA_Move'") };
		if (Asset.Succeeded())
		{
			Move = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Look.IA_Look'") };
		if (Asset.Succeeded())
		{
			Look = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_RandomColor.IA_RandomColor'") };
		if (Asset.Succeeded())
		{
			RandomColor = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_SwordAttack.IA_SwordAttack'") };
		if (Asset.Succeeded())
		{
			SwordAttack = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
<<<<<<< HEAD
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_SwordSkill.IA_SwordSkill'") };
		if (Asset.Succeeded())
		{
			SwordSkill = Asset.Object;
		}
	}


	
=======
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Change1.IA_Change1'") };
		if (Asset.Succeeded())
		{
			Weapon1 = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Change2.IA_Change2'") };
		if (Asset.Succeeded())
		{
			Weapon2 = Asset.Object;
		}
	}
>>>>>>> cdaf7b7 (Add ChangeWeapon Inputs)
}
