// Copyright (c) 2022 Pocket Sized Animations


#include "Components/ProjectileManagerComponent.h"

// Sets default values for this component's properties
UProjectileManagerComponent::UProjectileManagerComponent()
{
	ProjectileCollisionParams.bTraceComplex = true;
	ProjectileCollisionParams.bReturnPhysicalMaterial = true;
	ProjectileCollisionParams.bReturnFaceIndex = true;


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
	
	
	/*process each projectile*/
	for (auto Projectile : Projectiles)	
	{
		ProcessProjectileMovement(Projectile);
		if (Projectile.bProjectileHit)
			ProcessProjectileHit(Projectile);
	}

}

void UProjectileManagerComponent::SpawnProjectile(FProjectile NewProjectile)
{

}

void UProjectileManagerComponent::ProcessProjectileMovement(FProjectile& Projectile)
{

}

void UProjectileManagerComponent::ProcessProjectileHit(FProjectile& Projectile)
{

}

