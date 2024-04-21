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
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Sprint.IA_Sprint'") };
		if (Asset.Succeeded())
		{
			Sprint = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Sprint.IA_Sprint'") };
		if (Asset.Succeeded())
		{
			SprintEnd = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Attack.IA_Attack'") };
		if (Asset.Succeeded())
		{
			Attack = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Skill.IA_Skill'") };
		if (Asset.Succeeded())
		{
			Skill = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
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
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_DodgeFwd.IA_DodgeFwd'") };
		if (Asset.Succeeded())
		{
			DodgeFwd = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_DodgeBwd.IA_DodgeBwd'") };
		if (Asset.Succeeded())
		{
			DodgeBwd = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_DodgeRight.IA_DodgeRight'") };
		if (Asset.Succeeded())
		{
			DodgeRight = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_DodgeLeft.IA_DodgeLeft'") };
		if (Asset.Succeeded())
		{
			DodgeLeft = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_TargetLock.IA_TargetLock'") };
		if (Asset.Succeeded())
		{
			TargetLock = Asset.Object;
		}
	} 
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_SwitchLeft.IA_SwitchLeft'") };
		if (Asset.Succeeded())
		{
			SwitchLeft = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_SwitchRight.IA_SwitchRight'") };
		if (Asset.Succeeded())
		{
			SwitchRight = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Change1.IA_Change1'") };
		if (Asset.Succeeded())
		{
			ChangeCharacter1 = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Change2.IA_Change2'") };
		if (Asset.Succeeded())
		{
			ChangeCharacter2 = Asset.Object;
		}
	}
	{
		static ConstructorHelpers::FObjectFinder<UInputAction> Asset
		{ TEXT("/Script/EnhancedInput.InputAction'/Game/Main/Input/IA_Grapple.IA_Grapple'") };
		if (Asset.Succeeded())
		{
			Grapple = Asset.Object;
		}
	}
}
