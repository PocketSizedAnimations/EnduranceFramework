// Copyright (c) 2022 Pocket Sized Animations


#include "Components/VehicleMovementComponent.h"

UVehicleMovementComponent::UVehicleMovementComponent()
{


	/*tick setup*/
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.bStartWithTickEnabled = true;
	PrimaryComponentTick.TickGroup = ETickingGroup::TG_PostPhysics;
	PrimaryComponentTick.bAllowTickOnDedicatedServer = true;

	/*replication*/
	SetIsReplicatedByDefault(true);
}