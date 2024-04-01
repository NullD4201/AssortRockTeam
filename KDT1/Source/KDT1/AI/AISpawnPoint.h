// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "AISpawnPoint.generated.h"

UCLASS()
class KDT1_API AAISpawnPoint : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AAISpawnPoint();

protected:
	USceneComponent* mRoot;

	UPROPERTY(EditAnywhere)

	TSubclassOf<class AAIPawn>	mSpawnClass;

	class AAIPawn* mSpawnAI;

	UPROPERTY(EditAnywhere)
	float	mSpawnTime;

	float	mAccTime;

	UPROPERTY(EditAnywhere)
	TArray<class APatrolPointActor*> mPatrolArray;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ClearSpawnObject();

private:
	void Spawn();
};
