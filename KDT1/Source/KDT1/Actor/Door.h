// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Components/BoxComponent.h"
#include "Door.generated.h"

UCLASS()
class KDT1_API ADoor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADoor();

	bool bIsPlayerInRange;

	UPROPERTY(VisibleAnywhere)
	UStaticMeshComponent* DoorMesh;

	// BoxComponent 선언
	UPROPERTY(VisibleAnywhere)
	UBoxComponent* BoxComponent; 

	/** 무언가가 구체 컴포넌트에 들어설 때 호출 */
	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, 
						class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex, 
						bool bFromSweep, 
						const FHitResult& SweepResult);

	/** 무언가가 구체 컴포넌트를 나설 때 호출 */
	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp,
						class AActor* OtherActor, 
						class UPrimitiveComponent* OtherComp, 
						int32 OtherBodyIndex);

	void OpenDoor();
	void CloseDoor();
	void ToggleDoor();

private:
	bool bIsOpen;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
};
