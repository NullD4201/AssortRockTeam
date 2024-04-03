// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "../Character/MainCharacter.h"

// Sets default values
ADoor::ADoor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

    DoorMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DoorMesh"));
    RootComponent = DoorMesh;

    BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("BoxComponent"));
    BoxComponent->SetupAttachment(RootComponent);
    BoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADoor::OnOverlapBegin);
    BoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADoor::OnOverlapEnd);

    bIsOpen = false;

}

void ADoor::OnOverlapBegin(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
    // 오버랩이 시작되면 플레이어가 범위 내에 있다고 표시
    if (OtherActor->IsA(AMainCharacter::StaticClass()))
    {
        bIsPlayerInRange = true;
    }
}

void ADoor::OnOverlapEnd(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
    if (OtherActor->IsA(AMainCharacter::StaticClass()))
    {
        bIsPlayerInRange = false;
    }
}

void ADoor::OpenDoor()
{
    // 문의 각도를 0,90,0 으로만듬
    DoorMesh->SetRelativeRotation(FRotator(0.f, 90.f, 0.f));
    bIsOpen = true;
}

void ADoor::CloseDoor()
{
    // 문의 각도를 0,0,0 [원래자리] 로만듬
    DoorMesh->SetRelativeRotation(FRotator(0.f, 0.f, 0.f));
    bIsOpen = false;
}

void ADoor::ToggleDoor()
{
    if (bIsPlayerInRange)
    {
        if (bIsOpen)
        {
            CloseDoor();
        }
        else
        {
            OpenDoor();
        }
    }
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();

    // 'F' 키에 ToggleDoor 함수를 바인딩
    InputComponent = NewObject<UInputComponent>(this);
    InputComponent->RegisterComponent();
    if (InputComponent)
    {
        InputComponent->BindAction("OpenCloseDoor", IE_Pressed, this, &ADoor::ToggleDoor);
    }

    // 초기에 플레이어가 범위 내에 없다고 설정
    bIsPlayerInRange = false;
	
}

