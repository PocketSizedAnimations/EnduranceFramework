// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryItemComponent.h"
#include "Components/InventoryManagerComponent.h"
#include "Events/ItemEvent.h"


/*replication*/
#include "Net/UnrealNetwork.h"

/*utilities*/
#include "TimerManager.h"

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
	else if (EquipLogic == EEquipCompletionLogic::Delayed)
		GetOwner()->GetWorldTimerManager().SetTimer(EquipHandler, this, &UInventoryItemComponent::EndEquip, EquipDelay, false);

	if (OnEquipBegin.IsBound())
		OnEquipBegin.Broadcast(GetOwner(), this, GetInventoryManager(), GetOwner()->GetOwner());
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

void UInventoryItemComponent::BeginUnequip()
{
	EquipState = EEquipState::Unequipping;

	if (UnequipLogic == EEquipCompletionLogic::Instant)
		EndUnequip();
	else if(UnequipLogic == EEquipCompletionLogic::Delayed)
		GetOwner()->GetWorldTimerManager().SetTimer(UnequipHandler, this, &UInventoryItemComponent::EndUnequip, UnequipDelay, false);

	if (OnUnequipBegin.IsBound())
		OnUnequipBegin.Broadcast(GetOwner(), this, GetInventoryManager(), GetOwner()->GetOwner());
}

void UInventoryItemComponent::EndUnequip()
{
	EquipState = EEquipState::InStorage;
	InventoryManager->OnUnequipFinished(GetOwner());

	for (auto Event : OnUnequipEvents)
	{
		if(Event != nullptr && Event->bEnabled)
			Event->OnItemEventActivated(GetOwner(), GetOwner()->GetOwner(), InventoryManager);
	}

	if(OnUnequipEnd.IsBound())
		OnUnequipEnd.Broadcast(GetOwner(), this, GetInventoryManager(), GetOwner()->GetOwner());

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

