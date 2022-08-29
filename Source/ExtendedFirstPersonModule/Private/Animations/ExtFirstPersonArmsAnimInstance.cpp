// Copyright (c) 2022 Pocket Sized Animations


#include "Animations/ExtFirstPersonArmsAnimInstance.h"
#include "InventoryModule/Public/Components/InventoryManagerComponent.h"
#include "InventoryModule/Public/Components/InventoryItemComponent.h"
#include "WeaponsModule/Public/Actors/Weapon.h"

void UExtFirstPersonArmsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	GetInventoryManager();
}

void UExtFirstPersonArmsAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);


}

void UExtFirstPersonArmsAnimInstance::OnUpdateItemStates()
{
	Super::OnUpdateItemStates();


}

void UExtFirstPersonArmsAnimInstance::UpdateCurrentlyEquippedItem()
{
	if (!GetInventoryManager())
		return;

	CurrentlyEquippedItem = GetInventoryManager()->GetCurrentlyEquippedItem();
}

void UExtFirstPersonArmsAnimInstance::UpdateItemEquipState()
{
	Super::UpdateItemEquipState();

	if (GetCurrentItemComponent() == nullptr) {
		CurrentItemState = EAnimState_ItemState::NoCurrentItem;
		return;
	}
		

	switch (GetCurrentItemComponent()->GetEquipState())
	{
		case EEquipState::Equipped:
			CurrentItemState = EAnimState_ItemState::Equipped;
			return;
		case EEquipState::Equipping:
			CurrentItemState = EAnimState_ItemState::Equipping;
			return;
		case EEquipState::Unequipping:
			CurrentItemState = EAnimState_ItemState::Unequipping;
			return;
		default:
			CurrentItemState = EAnimState_ItemState::NoCurrentItem;
	}
}

bool UExtFirstPersonArmsAnimInstance::HasWeaponEquipped()
{
	if (!CurrentlyEquippedItem)
		return false;

	else if (Cast<AWeapon>(CurrentlyEquippedItem))
		return true;

	else
		return false;
}

UInventoryManagerComponent* UExtFirstPersonArmsAnimInstance::GetInventoryManager()
{
	/*return cached InventoryManager*/
	if (InventoryManager != nullptr)
		return InventoryManager;


	if (TryGetPawnOwner())
	{
		/*cache find*/
		InventoryManager = Cast<UInventoryManagerComponent>(TryGetPawnOwner()->GetComponentByClass(UInventoryManagerComponent::StaticClass()));
		/*return find*/
		return InventoryManager;
	}
	
	return nullptr;
}

UInventoryItemComponent* UExtFirstPersonArmsAnimInstance::GetCurrentItemComponent()
{
	if (GetInventoryManager())
	{
		return GetInventoryManager()->GetItemComponent(CurrentlyEquippedItem);
	}

	return nullptr;
}
