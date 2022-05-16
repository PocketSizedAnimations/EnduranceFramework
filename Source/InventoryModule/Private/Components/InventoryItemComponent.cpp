// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryItemComponent.h"
#include "Components/InventoryManagerComponent.h"
#include "Events/ItemEvent.h"

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
}

void UInventoryItemComponent::EnableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(true);		
	}
}

void UInventoryItemComponent::DisableCollision()
{
	if (GetOwner())
	{
		GetOwner()->SetActorEnableCollision(false);
	}
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

