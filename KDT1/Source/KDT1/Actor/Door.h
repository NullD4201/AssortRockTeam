// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "../GameInfo.h"
#include "GameFramework/Actor.h"
#include "Door.generated.h"

UCLASS()
class KDT1_API ADoor : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
	UBoxComponent* OverlapComponent;

	UPROPERTY(EditAnywhere)
	UUserWidget* OpenMessageWidget;

	UPROPERTY(EditAnywhere)
	UUserWidget* CloseMessageWidget;
	
public:	
	// Sets default values for this actor's properties
	ADoor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	bool	bIsOpen;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void OpenDoor();
	void CloseDoor();

	UFUNCTION()
	void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

};
