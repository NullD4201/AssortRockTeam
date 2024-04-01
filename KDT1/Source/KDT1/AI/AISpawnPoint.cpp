// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"
#include "AIPawn.h"

// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

	mSpawnAI = nullptr;
	mAccTime = 0.f;
	mSpawnTime = 0.f;
}

// Called when the game starts or when spawned
void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();

	Spawn();
}

// Called every frame
void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mSpawnAI)
	{
		mAccTime += DeltaTime;

		if (mAccTime >= mSpawnTime)
		{
			Spawn();
		}
	}
}

void AAISpawnPoint::ClearSpawnObject()
{
	mSpawnAI = nullptr;
	mAccTime = 0.f;
}

void AAISpawnPoint::Spawn()
{
	if (!IsValid(mSpawnClass))
	{
		return;
	}

	FActorSpawnParameters	SpawnParameters;
	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAIPawn* DefaultObj = Cast<AAIPawn>(mSpawnClass.GetDefaultObject());
	float	HalfHeight = 0.f;
	if (IsValid(DefaultObj))
	{
		HalfHeight = DefaultObj->GetHalfHeight();
	}

	mSpawnAI = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass, GetActorLocation() + FVector(0.0, 0.0, HalfHeight), GetActorRotation(), SpawnParameters);
	mSpawnAI->SetSpawnPoint(this);
	mSpawnAI->SetPatrolArray(mPatrolArray);
}

