// Copyright (c) 2022 Pocket Sized Animations


#include "Subsystem/ProjectileSubsystem.h"
#include "DrawDebugHelpers.h"

// Sets default values for this component's properties
UProjectileSubsystem::UProjectileSubsystem()
{
	ProjectileCollisionParams.bTraceComplex = true;
	ProjectileCollisionParams.bReturnPhysicalMaterial = true;
	ProjectileCollisionParams.bReturnFaceIndex = true;

	bDebugProjectiles = true;

	/*ticking*/
	//PrimaryComponentTick.bCanEverTick = true;
}


// Called every frame
void UProjectileSubsystem::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);


	/*process each projectile*/
	for (auto& Projectile : Projectiles)
	{
		/*process movement updates*/
		if (!Projectile.bProjectileHit)
			ProcessProjectileMovement(Projectile, DeltaTime);

		/*if hit detected - process hit*/
		if (Projectile.bProjectileHit == true && Projectile.bHitProcessed == false)
			ProcessProjectileHit(Projectile);
	}
}

TStatId UProjectileSubsystem::GetStatId() const
{
	return TStatId();
}

void UProjectileSubsystem::SpawnProjectile(FProjectile& NewProjectile)
{
	Projectiles.Add(NewProjectile);
}

void UProjectileSubsystem::ProcessProjectileMovement(FProjectile& Projectile, float DeltaTime)
{
	FVector NextLocationUpdate = Projectile.Location + (Projectile.ForwardDirection * Projectile.Velocity * DeltaTime);
	Projectile.PreviousLocation = Projectile.Location;

	/*apply gravity*/
	if (IsProjectileBeyondEffectiveRange(Projectile))
		ApplyGravity(Projectile, NextLocationUpdate, DeltaTime);

	/*make sure we clear && updated the ignored actors to match this current projectile for this specific move*/
	UpdateCollisionParamsIgnoredActorsList(Projectile);

	/*process move*/
	/*if colliding hit detected*/
	bool bHit = GetWorld()->LineTraceSingleByChannel(Projectile.HitResults, Projectile.Location, NextLocationUpdate, TraceChannel, ProjectileCollisionParams);
	if (bHit)
	{
		Projectile.Location = Projectile.HitResults.Location;
		Projectile.bProjectileHit = true;
	}

	/*no hit - move forward*/
	else
	{
		Projectile.Location = NextLocationUpdate;
	}

	/*update how far we've traveled*/
	Projectile.DistanceTraveled += FVector::Distance(Projectile.Location, Projectile.PreviousLocation);


	/*debug tracing line*/
	if (bDebugProjectiles)
		DrawDebugLine(GetWorld(), Projectile.PreviousLocation, bHit ? Projectile.HitResults.Location : Projectile.Location, GetTraceDebugColor(Projectile), false, 3.5f, 10, 2.0f);

}


/*ApplyGravity() - each Tick() this simply applies a gravitational force onto the projectile, pulling it downwards (by default) 9.8m/s
* this then caps out at 920.0uu/s (by default) since that's the terminal velocity (the max velocity an object can hit) of a typical bullet
* once that's calculated we then simply adjust the currenty movement update downward by that GravityStrength for each update we receive simulating a very
* basic idea of gravity pulling down on the bullets
*/
void UProjectileSubsystem::ApplyGravity(FProjectile& Projectile, FVector& MovementUpdate, float DeltaTime)
{
	/*update the strength of gravity on the bullet*/
	if (Projectile.GravityStrength < Projectile.TerminalFallVelocity)
		Projectile.GravityStrength += Gravity * DeltaTime;

	/*apply gravity (downward force) to this movement*/
	MovementUpdate += (FVector(0, 0, -1) * Projectile.GravityStrength) * DeltaTime;
}

void UProjectileSubsystem::ProcessProjectileHit(FProjectile& Projectile)
{
	if (Projectile.bHitProcessed == true)
		return;

	FDamageEvent DamageEvent;

	if (Projectile.HitResults.GetActor())
		Projectile.HitResults.GetActor()->TakeDamage(Projectile.GetDamage(), DamageEvent, Projectile.Instigator, Projectile.DamageCauser);

	Projectile.bHitProcessed = true; //mark we've already processed this one

	/*notify delegates*/
	if (OnProjectileHit.IsBound())
		OnProjectileHit.Broadcast(Projectile);

	/*show impact if debugging*/
	if (bDebugProjectiles)
		DrawDebugSphere(GetWorld(), Projectile.HitResults.Location, 8, 8, FColor::Red, false, 3.5f);
}

bool UProjectileSubsystem::IsProjectileBeyondEffectiveRange(FProjectile& Projectile)
{
	if (Projectile.DistanceTraveled > Projectile.EffectiveRange)
		return true;
	else
		return false;
}

void UProjectileSubsystem::UpdateCollisionParamsIgnoredActorsList(FProjectile& Projectile)
{
	ProjectileCollisionParams.ClearIgnoredActors();
	ProjectileCollisionParams.AddIgnoredActors(Projectile.IgnoredActors);
}

FColor UProjectileSubsystem::GetTraceDebugColor(FProjectile& Projectile)
{
	/*if Gravity is ~ full strength*/
	if (Projectile.GravityStrength >= (Projectile.TerminalFallVelocity * .90f))
		return FColor::Red;

	/*if gravity has begun to take ahold*/
	if (IsProjectileBeyondEffectiveRange(Projectile))
		return FColor::Yellow;

	/*max-damage && max-velocity*/
	return FColor::Green;
}

