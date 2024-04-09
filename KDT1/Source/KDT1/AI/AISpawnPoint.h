// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIPawn.h"
#include "PatrolPointActor.h"
#include "Components/ArrowComponent.h"
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
	USceneComponent*	mRoot;

#if	WITH_EDITORONLY_DATA
	UArrowComponent*	mDirectionArrow;
#endif

	UPROPERTY(EditAnywhere)
	TSubclassOf<AAIPawn>	mSpawnClass;

	AAIPawn* mSpawnAIPawn;

	UPROPERTY(EditAnywhere)
	float	mSpawnTime;

	float	mAccessTime;

	UPROPERTY(EditAnywhere)
	TArray<APatrolPointActor*>	mPatrolArray;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	void ClearSpawnObject();

private:
	void Spawn();

};
