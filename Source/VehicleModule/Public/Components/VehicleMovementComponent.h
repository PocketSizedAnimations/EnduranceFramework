// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "VehicleMovementComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Vehicles), meta = (BlueprintSpawnableComponent))
class VEHICLEMODULE_API UVehicleMovementComponent : public UPawnMovementComponent
{
	GENERATED_BODY()
public:


	//===========================================================================
	//=================================FUNCTIONS=================================
	//===========================================================================
	UVehicleMovementComponent();
	
};
