// Copyright (c) 2022 Pocket Sized Animations


#include "Components/ProjectileManagerComponent.h"

// Sets default values for this component's properties
UProjectileManagerComponent::UProjectileManagerComponent()
{

	/*ticking*/
	PrimaryComponentTick.bCanEverTick = true;
}


// Called when the game starts
void UProjectileManagerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UProjectileManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

