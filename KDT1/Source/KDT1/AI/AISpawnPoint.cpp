// Fill out your copyright notice in the Description page of Project Settings.


#include "AISpawnPoint.h"

// Sets default values
AAISpawnPoint::AAISpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));

#if WITH_EDITORONLY_DATA
	// mDirectionArrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Root"));
	
	// mDirectionArrow->SetupAttachment(mRoot);
#endif

	SetRootComponent(mRoot);

	mRoot->bVisualizeComponent = true;

	mSpawnAIPawn = nullptr;
	mAccessTime = 0.f;
	mSpawnTime = 0.f;
}

// Called when the game starts or when spawned
void AAISpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AAISpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (!mSpawnAIPawn)
	{
		mAccessTime += DeltaTime;

		if (mAccessTime >= mSpawnTime)
		{
			Spawn();
		}
	}
}

void AAISpawnPoint::ClearSpawnObject()
{
	mSpawnAIPawn = nullptr;
	mAccessTime = 0.f;
}

void AAISpawnPoint::Spawn()
{
	if (!IsValid(mSpawnClass))
	{
		return;
	}

	FActorSpawnParameters	SpawnParameters;

	SpawnParameters.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn;

	AAIPawn* DefaultObject = Cast<AAIPawn>(mSpawnClass.GetDefaultObject());

	float	HalfHeight = 0.f;

	if (IsValid(DefaultObject))
	{
		HalfHeight = DefaultObject->GetHalfHeight();
	}

	mSpawnAIPawn = GetWorld()->SpawnActor<AAIPawn>(mSpawnClass, GetActorLocation() + FVector(0., 0., (double) HalfHeight), GetActorRotation(), SpawnParameters);

	mSpawnAIPawn->SetSpawnPoint(this);

	mSpawnAIPawn->SetPatrolArray(mPatrolArray);
}

