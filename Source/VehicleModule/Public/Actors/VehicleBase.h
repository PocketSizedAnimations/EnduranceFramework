// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "VehicleBase.generated.h"

UCLASS()
class VEHICLEMODULE_API AVehicleBase : public APawn
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere, Category = "Rendering")
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleAnywhere, Category = "Vehicle")
		class UEngineComponent* Engine;

	UPROPERTY(VisibleAnywhere, Category = "Vehicle")
		class UVehicleMovementComponent* VehicleMovement;



	/*input names - add these to your Input Configuration*/
	UPROPERTY(VisibleAnywhere, Category = "Input")
		FName AccelerateInputName = "Accelerate";
	UPROPERTY(VisibleAnywhere, Category = "Input")
		FName BrakeInputName = "Brake";
	UPROPERTY(VisibleAnywhere, Category = "Input")
		FName StartEngineInputName = "StartEngine";
	UPROPERTY(VisibleAnywhere, Category = "Input")
		FName StopEngineInputName = "StopEngine";


	//===========================================================================================
	//=========================================FUNCTIONS=========================================
	//===========================================================================================

public:
	// Sets default values for this pawn's properties
	AVehicleBase(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;


	UFUNCTION()
		virtual void Accelerate(float Value);
	UFUNCTION()
		virtual void Brake(float Value);	
	UFUNCTION()
		virtual void StartEngine();
	UFUNCTION()
		virtual void StopEngine();

	

};
