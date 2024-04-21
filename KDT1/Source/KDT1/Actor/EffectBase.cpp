// Fill out your copyright notice in the Description page of Project Settings.


#include "EffectBase.h"

// Sets default values
AEffectBase::AEffectBase()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAudio = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio"));

	SetRootComponent(mAudio);
}

// Called when the game starts or when spawned
void AEffectBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEffectBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEffectBase::SetSoundAsset(const FString& Path)
{
	USoundBase* Sound = LoadObject<USoundBase>(nullptr, *Path);

	SetSoundAsset(Sound);
}

void AEffectBase::SetSoundAsset(USoundBase* Sound)
{
	if (IsValid(Sound))
	{
		mAudio->SetSound(Sound);
		mAudio->Play();
	}
}

