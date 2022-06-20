// Copyright (c) 2022 Pocket Sized Animations


#include "Components/ProjectileSpawnerComponent.h"
#include "Subsystem/ProjectileSubsystem.h"

/*gamemodes*/
#include "GameFramework/GameModeBase.h"
#include "GameFramework/GameStateBase.h"

/*replication*/
#include "Net/UnrealNetwork.h"


/*setup replication*/
void UProjectileSpawnerComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION(UProjectileSpawnerComponent, bFiring, COND_SkipOwner);	
}

// Sets default values for this component's properties
UProjectileSpawnerComponent::UProjectileSpawnerComponent()
{	
	/*replication*/
	SetIsReplicatedByDefault(true);
	/*ticking*/
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UProjectileSpawnerComponent::BeginPlay()
{
	Super::BeginPlay();
}


// Called every frame
void UProjectileSpawnerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}


/*BeginFire() - function that begins firing (authoriative + simulation) for server/clients
*  for remote-clients this is called anytime they get a bFiring variable update
*
*
* 
*/

void UProjectileSpawnerComponent::BeginFire()
{
	/*already-firing check*/
	if (IsFiring())
		return;
	
	/*owning client? - notify server*/
	if (GetNetMode() == NM_Client && IsLocallyControlled())
		ServerNotify_BeginFire();

	/*server | owning-client | remote-client - begin firing*/
	PerformFire();
}

void UProjectileSpawnerComponent::EndFire()
{
	/*owning client? - notify server*/
	if (GetNetMode() == NM_Client && IsLocallyControlled())
		ServerNotify_EndFire();

	bFiring = false;
}

bool UProjectileSpawnerComponent::ServerNotify_BeginFire_Validate()
{
	return true;
}

/*ServerNotify_BeginFire() - simply called by an owning client and lets the server know they've begun firing*/
void UProjectileSpawnerComponent::ServerNotify_BeginFire_Implementation()
{
	BeginFire();
}

bool UProjectileSpawnerComponent::ServerNotify_EndFire_Validate()
{
	return true;
}

/*ServerNotify_EndFire() - simply called by an ownin client to let the server know they've stopped firing*/
void UProjectileSpawnerComponent::ServerNotify_EndFire_Implementation()
{
	EndFire();
}


bool UProjectileSpawnerComponent::IsFiring()
{
	return bFiring;
}

/* PerformFire() - loopable function that performs the actual firing
*  don't call directly - use BeginFire() instead to perform various checks first
* 
* 
*/
void UProjectileSpawnerComponent::PerformFire()
{
	/*perform actual firing*/
	bFiring = true;

	PerformShot();
}

/*creates a projectile or insta-hit trace based on info - 
* don't call directly
* should only be called from PerformFire()*/
void UProjectileSpawnerComponent::PerformShot()
{
	/*projecitle based*/
	if (ProjectileType == EProjectileType::Projectile)
	{
		if (GetProjectileSubsystem())
		{
			/*generate new projectile data*/
			FProjectile Projectile = FProjectile(ProjectileInfo, 
					GetProjectileSpawnTransform().GetLocation(), 
					GetProjectileSpawnTransform().GetRotation().GetForwardVector(), 
					GetOwner(), 
					GetOwningPawn(),
					GetOwningPlayerController());

			/*spawn projectile*/
			GetProjectileSubsystem()->SpawnProjectile(Projectile);
		}
	}
	/*insta-hit tracing*/
	else if (ProjectileType == EProjectileType::Instahit)
	{

	}
}


/*OnRep_FiringStateChanged() - called whenever bFiring changes - allows remote-clients to initiate the simulation with low overhead*/
void UProjectileSpawnerComponent::OnRep_FiringStateChanged()
{
	if (bFiring)
		BeginFire();
	else
		EndFire();
}

FTransform UProjectileSpawnerComponent::GetProjectileSpawnTransform()
{
	FTransform TraceTransform = GetComponentTransform(); //fallback to our own location if not overridden

	switch (ProjectileTraceType)
	{
		/*when using the PlayerView - if we're the server (authorative simulation) or the owning client we will use the PlayerController's view
			if we-re a remote client we will use an approximation start spot of the pawn's View Location (Actor Location + EyeHeight) and the Epic Replicated
			Base Aim Rotation (which is an approximation of the controller rotation sent to clients) */
		case EProjectileTraceType::PlayerView:
		{
			/*server*/
			if (GetNetMode() < NM_Client && GetOwningPlayerController()|| (GetOwningPlayerController() && GetOwningPlayerController()->IsLocalPlayerController()))
			{			
				FVector _location;
				FRotator _rotation;

				GetOwningPlayerController()->GetPlayerViewPoint(_location, _rotation);
				TraceTransform.SetLocation(_location);
				TraceTransform.SetRotation(_rotation.Quaternion());
				break;
			}
			/*remote clients || if no PlayerController was found*/
			else if (APawn* P = GetOwningPawn())
			{	
				FVector _location = P->GetPawnViewLocation(); //Pawn's Location + EyeHeight offset
				FRotator _rotation = P->GetBaseAimRotation(); //Epic replicated approxemiation of controller rotation
				
				TraceTransform.SetLocation(_location);
				TraceTransform.SetRotation(_rotation.Quaternion());
				break;
			}
			else
				break;
		}
		case EProjectileTraceType::Component:
		{
			TraceTransform = GetComponentTransform(); //location of (this) specific Projectile relative to owner
			break;
		}
		case EProjectileTraceType::Socket:
		{
			TraceTransform = GetSocketTransformFromOwner(); //attempts to find the socket transform on the first skeletal/static mesh it can find
			break;
		}		
	}

	return TraceTransform;
}

APlayerController* UProjectileSpawnerComponent::GetOwningPlayerController()
{
	if (PC != nullptr)
		return PC;

	int32 i = 0;

	/*fetch && cache PC reference*/
	AActor* _owner = GetOwner(); //set the initial owner to the component's owner
	while (i < 20)
	{
		/*if we've run out of owners - break out of the loop*/
		if (_owner == nullptr)
			break;
		/*if we're a PlayerController - return us*/
		if (Cast<APlayerController>(_owner))
		{			
			PC = Cast<APlayerController>(_owner);
			return PC;
		}
		/*otherwise - move up the owner chain*/
		else
			_owner = _owner->GetOwner();
	}
	
	/*return null if we found nothing*/
	return nullptr;
}

APawn* UProjectileSpawnerComponent::GetOwningPawn()
{
	int32 i = 0;

	/*fetch && cache PC reference*/
	AActor* _owner = GetOwner(); //set the initial owner to the component's owner
	while (i < 20)
	{
		/*if we've run out of owners - break out of the loop*/
		if (_owner == nullptr)
			break;
		/*if we're a Pawn - return us*/
		if (Cast<APawn>(_owner))
			return Cast<APawn>(_owner);
		/*otherwise - move up the owner chain*/
		else
			_owner = _owner->GetOwner();
	}

	/*return null if we found nothing*/
	return nullptr;
}

bool UProjectileSpawnerComponent::IsLocallyControlled()
{
	if (GetOwningPawn())
		return GetOwningPawn()->IsLocallyControlled();
	else
		return false;
}

FTransform UProjectileSpawnerComponent::GetSocketTransformFromOwner()
{
	if (USkeletalMeshComponent* MeshComp = Cast<USkeletalMeshComponent>(GetOwner()->GetComponentByClass(USkeletalMeshComponent::StaticClass())))
	{
		if (MeshComp->SkeletalMesh != nullptr)
		{
			return MeshComp->GetSocketTransform(ProjectileSocketName);
		}
	}

	if (UStaticMeshComponent* MeshComp = Cast<UStaticMeshComponent>(GetOwner()->GetComponentByClass(UStaticMeshComponent::StaticClass())))
	{
		if(MeshComp->GetStaticMesh())
			return MeshComp->GetSocketTransform(ProjectileSocketName);
	}

	return FTransform();
}




UProjectileSubsystem* UProjectileSpawnerComponent::GetProjectileSubsystem()
{
	if (ProjectileSubsystem != nullptr)
		return ProjectileSubsystem;

	ProjectileSubsystem = GetWorld()->GetSubsystem<UProjectileSubsystem>();
	return ProjectileSubsystem;
}
