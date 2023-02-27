// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/MeleeWeapon.h"
#include "InventoryModule/Public/Components/InventoryItemComponent.h"
#include "GameFramework/Character.h"
#include "Components/SkeletalMeshComponent.h"
#include "DrawDebugHelpers.h"

AMeleeWeapon::AMeleeWeapon(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	//PrimaryActorTick.TickInterval = 
}

void AMeleeWeapon::Tick(float DeltaTime)
{
	if (bAttacking)
		PerformWeaponTrace();
}



void AMeleeWeapon::BeginLightAttack()
{
	BeginFire();
	//LightAttack->Slot
}

void AMeleeWeapon::BeginHeavyAttack()
{
	BeginFire();
}

void AMeleeWeapon::BeginThrustingAttack()
{
	BeginFire();
}

void AMeleeWeapon::BeginFire()
{
	bAttacking = true;
	OnAttackBegin();
}

void AMeleeWeapon::EndFire()
{
	bAttacking = false;
	OnAttackEnd();
}


void AMeleeWeapon::OnAttackBegin()
{

}

void AMeleeWeapon::OnAttackEnd()
{

}

void AMeleeWeapon::PerformWeaponTrace()
{
	FHitResult HitResults;
	FVector TraceStart = Mesh->GetSocketLocation(TraceStartSocketName);
	FVector TraceEnd = Mesh->GetSocketLocation(TraceEndSocketName);
	FCollisionQueryParams CollisionParams;
	
	/*filter out our own model and our owner*/
	CollisionParams.AddIgnoredActor(this);
	CollisionParams.AddIgnoredActor(ItemComponent->GetOwningActor());
	

#if WITH_EDITOR
	if (bDebugTrace)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd,FColor::Orange,false,2.5f,2,3.0f);
	}
#endif

	if (GetWorld()->LineTraceSingleByChannel(HitResults, TraceStart, TraceEnd, TraceChannel, CollisionParams))
	{
#if WITH_EDITOR
		if (bDebugTrace)
			DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Green, false, 2.5f, 2, 3.5f);
#endif
		OnTraceHit(HitResults);
	}
}

void AMeleeWeapon::OnTraceHit(FHitResult HitResults)
{
#if WITH_EDITOR
	if (bDebugTrace)
	{
		FString HitString = "Hit Actor :" + GetNameSafe(HitResults.GetActor());
		GEngine->AddOnScreenDebugMessage(223, 3.0f, FColor::Green,HitString, true);
	}

#endif
}
