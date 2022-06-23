// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryItemComponent.h"
#include "Components/InventoryManagerComponent.h"
#include "Events/ItemEvent.h"

/*replication*/
#include "Net/UnrealNetwork.h"

void UInventoryItemComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UInventoryItemComponent, bCollisionEnabled);
}

// Sets default values for this component's properties
UInventoryItemComponent::UInventoryItemComponent()
{
	/*replication*/
	SetIsReplicatedByDefault(true);
	/*ticking*/
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UInventoryItemComponent::BeginPlay()
{
	Super::BeginPlay();	
}


void UInventoryItemComponent::BeginEquip()
{
	EquipState = EEquipState::Equipping;

	
	if (EquipLogic == EEquipCompletionLogic::Instant)
		EndEquip();

	//else if(EquipLogic == EEquipCompletionLogic::Delayed)
}

void UInventoryItemComponent::EndEquip()
{	
	EquipState = EEquipState::Equipped;
	InventoryManager->OnEquipFinished(GetOwner());

	for (auto Event : OnEquipEvents)
	{
		if (Event != nullptr && Event->bEnabled)
			Event->OnItemEventActivated(GetOwner(), GetOwner()->GetOwner(), InventoryManager);
	}

	if(OnEquipEnd.IsBound())
		OnEquipEnd.Broadcast(GetOwner(), this, GetInventoryManager(), GetOwner()->GetOwner());
}

void UInventoryItemComponent::EnableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(true);		
	}

	if(GetNetMode() < NM_Client)
		bCollisionEnabled = true;
}

void UInventoryItemComponent::DisableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(false);
	}

	if (GetNetMode() < NM_Client)
		bCollisionEnabled = false;
}

void UInventoryItemComponent::OnRep_CollisionChanged()
{
	if (bCollisionEnabled)
		EnableCollision();
	else
		DisableCollision();
}

void UInventoryItemComponent::EnableVisibility()
{
	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(false);
	}
}

void UInventoryItemComponent::DisableVisibility()
{
	if (GetOwner())
	{
		GetOwner()->SetActorHiddenInGame(true);
	}
}

