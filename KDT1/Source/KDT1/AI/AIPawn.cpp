// Fill out your copyright notice in the Description page of Project Settings.


#include "AIPawn.h"

#include "AIController.h"
#include "AISpawnPoint.h"
#include "PatrolPointActor.h"
#include "Components/ProgressBar.h"

// Sets default values
AAIPawn::AAIPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	mAttackEnd = false;

	mCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Body"));
	mMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("Mesh"));
	mWeaponMesh = CreateDefaultSubobject<USkeletalMeshComponent>(TEXT("WeaponMesh"));
	mMovement = CreateDefaultSubobject<UFloatingPawnMovement>(TEXT("Movement"));
	mHealthBar = CreateDefaultSubobject<UWidgetComponent>(TEXT("Health Bar Widget"));

	mMovement->SetUpdatedComponent(mCapsule);

	SetRootComponent(mCapsule);

	mMesh->SetupAttachment(mCapsule);
	mCapsule->SetRelativeLocation(FVector(0, 0, 0));
	mWeaponMesh->SetupAttachment(mMesh, "weapon");
	mHealthBar->SetupAttachment(GetRootComponent());

	mHealthBar->SetRelativeScale3D(FVector(0.3, 0.3, 0.3));
	mHealthBar->SetRelativeLocation(FVector(0, 0, 100));

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	static ConstructorHelpers::FClassFinder<AAIController> AIClass(TEXT("/Script/CoreUObject.Class'/Script/KDT1.SoldierAIController_C'"));

    if (AIClass.Succeeded())
    {
	    AIControllerClass = AIClass.Class;
    }

	static ConstructorHelpers::FClassFinder<UUserWidget> HealthBarWidget(TEXT("/Script/UMGEditor.WidgetBlueprint'/Game/Main/UI/SoldierHealthBar.SoldierHealthBar_C'"));

    if (HealthBarWidget.Succeeded())
    {
	    mHealthBar->SetWidgetClass(HealthBarWidget.Class);
    }

	mSpawnPoint = nullptr;

	mPatrolIndex = -1;
	mPatrolDir = 1;

	mAIInfo = nullptr;
}

// Called when the game starts or when spawned
void AAIPawn::BeginPlay()
{
	Super::BeginPlay();

	mPatrolIndex = 1;
}

void AAIPawn::EndPlay(const EEndPlayReason::Type EndPlayReason)
{
	Super::EndPlay(EndPlayReason);

	if (mSpawnPoint)
	{
		mSpawnPoint->ClearSpawnObject();
	}

	if (mAIInfo)
	{
		delete mAIInfo;
	}
}

void AAIPawn::SetPatrolArray(const TArray<APatrolPointActor*>& PatrolArray)
{
	if (PatrolArray.IsEmpty())
	{
		return;
	}

	mPatrolArray = PatrolArray;

	FVector StartPoint = GetActorLocation() - FVector(0, 0, GetHalfHeight());

	mPatrolPointArray.Add(StartPoint);

	for (auto Point : mPatrolArray)
	{
		mPatrolPointArray.Add(Point->GetActorLocation());
	}
}

void AAIPawn::ChangeAIAnimType(uint8 AnimType)
{
}

void AAIPawn::OnConstruction(const FTransform& Transform)
{
	Super::OnConstruction(Transform);
}

// Called every frame
void AAIPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	FVector Dir = GetMovementComponent()->Velocity;
	Dir.Z = 0.f;
	Dir.Normalize();

	mHealthBar->SetRelativeRotation(FRotator(0.0, Dir.Rotation().Yaw, 0.0));
}

float AAIPawn::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	DamageAmount = Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);

	return DamageAmount;
}