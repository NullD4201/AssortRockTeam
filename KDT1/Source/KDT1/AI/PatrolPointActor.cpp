// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolPointActor.h"

// Sets default values
APatrolPointActor::APatrolPointActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mRoot = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	mTrigger = CreateDefaultSubobject<UBoxComponent>(TEXT("Trigger"));

	SetRootComponent(mRoot);

	mTrigger->SetupAttachment(mRoot);

	mTrigger->SetBoxExtent(FVector(30, 30, 100));
	mTrigger->SetRelativeLocation(FVector(0, 0, 100));

	mRoot->bVisualizeComponent = true;
}

// Called when the game starts or when spawned
void APatrolPointActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolPointActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

