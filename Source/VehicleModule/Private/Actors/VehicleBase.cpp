// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/VehicleBase.h"
#include "Components/EngineComponent.h"
#include "Components/VehicleMovementComponent.h"
#include "..\..\Public\Actors\VehicleBase.h"

// Sets default values
AVehicleBase::AVehicleBase(const FObjectInitializer& ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("MeshComponent"));
	if (Mesh)
	{
		SetRootComponent(Mesh);
	}

	Engine = ObjectInitializer.CreateDefaultSubobject<UEngineComponent>(this, TEXT("EngineComponent"));
	if (Engine)
	{
		Engine->SetupAttachment(Mesh);
	}

	VehicleMovement = ObjectInitializer.CreateDefaultSubobject<UVehicleMovementComponent>(this, TEXT("VehicleMovementComponent"));

	/*replication configuration*/
	FRepMovement RepMovement = GetReplicatedMovement();
	RepMovement.LocationQuantizationLevel = EVectorQuantization::RoundTwoDecimals;
	RepMovement.VelocityQuantizationLevel = EVectorQuantization::RoundOneDecimal;
	RepMovement.RotationQuantizationLevel = ERotatorQuantization::ShortComponents;
	SetReplicatedMovement(RepMovement);

	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AVehicleBase::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AVehicleBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AVehicleBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(PlayerInputComponent);

	PlayerInputComponent->BindAxis(AccelerateInputName,this,&AVehicleBase::Accelerate);
	PlayerInputComponent->BindAxis(BrakeInputName, this, &AVehicleBase::Brake);

	PlayerInputComponent->BindAction(StartEngineInputName, EInputEvent::IE_Pressed, this, &AVehicleBase::StartEngine);
	PlayerInputComponent->BindAction(StopEngineInputName, EInputEvent::IE_Pressed, this, &AVehicleBase::StopEngine);
}

void AVehicleBase::Accelerate(float Value)
{	
	VehicleMovement->AddInputVector(GetActorForwardVector() * Value);
}

void AVehicleBase::Brake(float Value)
{

}

void AVehicleBase::StartEngine()
{
	Engine->StartEngine();
}

void AVehicleBase::StopEngine()
{
	Engine->StopEngine();
}

