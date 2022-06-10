// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryManagerComponent.h"
#include "Components/InventoryItemComponent.h"
#include "Misc/InventoryTemplate.h"
#include "Blueprint/UserWidget.h"
#include "UI/InventoryContainerWidget.h"

// Sets default values for this component's properties
UInventoryManagerComponent::UInventoryManagerComponent()
{
	/*replication*/
	SetIsReplicatedByDefault(true);	

	/*ticking*/
	PrimaryComponentTick.bCanEverTick = false;
	PrimaryComponentTick.bStartWithTickEnabled = false;
}


// Called when the game starts
void UInventoryManagerComponent::BeginPlay()
{
	Super::BeginPlay();

	/*spawn the default inventory*/
	if(Inventory.Num() == 0)//we check if Inventory == 0 because BeginPlay() is called multiple times, so this saves overhead
		SpawnDefaultInventory();
}

void UInventoryManagerComponent::SpawnInventoryFromTemplate(UInventoryTemplate* InventoryTemplate, bool bClearExisting)
{
	if (!InventoryTemplate)
		return;

	if (bClearExisting)
		ClearInventory();

	SpawnInventory(InventoryTemplate->Inventory, bClearExisting);
}

void UInventoryManagerComponent::SpawnDefaultInventory()
{
	/*safety check*/
	if (GetNetMode() == NM_Client) 
		return;

	SpawnInventory(DefaultItems, true);
}

void UInventoryManagerComponent::SpawnInventory(TArray<TSubclassOf<AActor>> Items, bool bClearExisting)
{
	/*server-check*/
	if (GetOwner() == nullptr || GetOwner()->GetNetMode() == NM_Client)
		return;
	
	/*destroy existing inventory*/
	if (bClearExisting)
		ClearInventory();

	/*initialize*/
	FActorSpawnParameters SpawnParams;
	SpawnParams.bNoFail = true;
	SpawnParams.Owner = GetOwner();
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;	
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetOwner()->GetActorLocation());
	SpawnTransform.SetRotation(GetOwner()->GetActorRotation().Quaternion());
	SpawnTransform.SetScale3D(FVector(1));

	/*auto-equip*/
	AActor* AutoEquip = nullptr;

	for (TSubclassOf<AActor> ItemClass : Items)
	{		
		/*skip blank entries*/
		if (ItemClass == nullptr)
			continue;

		AActor* Item = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnTransform, SpawnParams);
		if (Item)
		{
			if (UInventoryItemComponent* ItemComp = GetItemComponent(Item))
			{				
				AddItem(ItemComp->GetOwner());
				
				if (ShouldAutoEquip(Item))
					AutoEquip = Item;
			}
		}
	}

	if (AutoEquip != nullptr)
		Equip(AutoEquip);
}

void UInventoryManagerComponent::ClearInventory()
{

}


//=====================================
//==============EQUIPPING==============
//=====================================

void UInventoryManagerComponent::Equip(AActor* Item)
{
	bool bInstantComplete = false;

	/*validation check*/
	if (!bCanEquipItems || Item == nullptr)
		return;
	
	/*ensure-registration is complete*/
	RegisterItem(Item);
	
	/*if we already have the item equipped - go ahead and auto-unequip it*/
	if (Item == CurrentlyEquipped)
	{
		Unequip(CurrentlyEquipped);
		return;
	}

	/*unequip anything we already have first*/
	if (CurrentlyEquipped != nullptr)
	{
		PendingEquip = Item;
		Unequip(Item);
		return;
	}

	/*mark this item as pending equip*/
	PendingEquip = Item;

	/*notify the component it's being equipped */
	if(UInventoryItemComponent* ItemComp = GetItemComponent(Item))
	{ 
		ItemComp->BeginEquip();		
	}
}

/*callback function - should be triggered by the item itself*/
void UInventoryManagerComponent::OnEquipFinished(AActor* Item)
{
	if (Item == nullptr)
		return;

	CurrentlyEquipped = Item;
	PendingEquip = nullptr;

}

void UInventoryManagerComponent::Unequip(AActor* Item)
{

}

void UInventoryManagerComponent::OnUnequipFinished(AActor* Item)
{		
	if (PendingEquip)
	{			
		Equip(PendingEquip);
	}
}

bool UInventoryManagerComponent::ShouldAutoEquip(AActor* Item)
{
	if (!Item)
		return false;

	if (UInventoryItemComponent* ItemComp = GetItemComponent(Item))
	{
		if (ItemComp->bAutoEquip)
			return true;
	}
	
	return false;
}



//=======================================
//============ITEM MANAGEMENT============
//=======================================
bool UInventoryManagerComponent::ContainsItem(AActor* Item)
{
	/*safety check*/
	if (!Item)
		return false;

	if (Inventory.Contains(Item))
		return true;
	else
		return false;
}

bool UInventoryManagerComponent::AddItem(AActor* Item)
{
	if (!Item)
		return false;
	

	/*add to inventory list*/
	int32 i = Inventory.Add(Item);		
	if (i >= 0)
	{
		/*set the Item's ownering to our owner && provide InventoryManager reference*/
		RegisterItem(Item);
		/*disables collision & hides model*/
		StoreItem(Item);
		//Item->b

		return true;
	}		
	else
		return false;
}

bool UInventoryManagerComponent::RemoveItem(AActor* Item)
{
	if (!Item)
		return false;

	Item->SetOwner(nullptr);

	return false;
}

void UInventoryManagerComponent::DropItem(AActor* Item)
{
	if (!Item)
		return;

	/*make sure we remove it from us*/
	RemoveItem(Item);

}


void UInventoryManagerComponent::StoreItem(AActor* Item)
{
	if (UInventoryItemComponent* ItemComp = Cast<UInventoryItemComponent>(Item->GetComponentByClass(UInventoryItemComponent::StaticClass())))
	{
		/*safety check*/
		if (ContainsItem(Item) == false)
		{
			AddItem(Item);
		}

		ItemComp->DisableCollision();
		ItemComp->DisableVisibility();
	}
}

void UInventoryManagerComponent::RegisterItem(AActor* Item)
{
	if (!Item)
		return;

	if (UInventoryItemComponent* ItemComp = Cast<UInventoryItemComponent>(Item->GetComponentByClass(UInventoryItemComponent::StaticClass())))
	{
		Item->SetOwner(GetOwner());
		ItemComp->InventoryManager = this;
	}
}

UInventoryItemComponent* UInventoryManagerComponent::GetItemComponent(AActor* Item)
{
	UInventoryItemComponent* ReturnItem = Cast<UInventoryItemComponent>(Item->GetComponentByClass(UInventoryItemComponent::StaticClass()));

	return ReturnItem;
}



//==============================
//==============UI==============
//==============================
void UInventoryManagerComponent::OpenInventoryUI(APlayerController* Controller)
{
	/*safety check*/
	if (!Controller || !InventoryUIClass)
		return;

	InventoryWidget = CreateWidget<UInventoryContainerWidget>(Controller, InventoryUIClass, FName("InventoryContainerWidget"));
	if (InventoryWidget)
	{
		InventoryWidget->AddToViewport();
		InventoryWidget->SetFocus();		
	}
}

void UInventoryManagerComponent::CloseInventoryUI(APlayerController* Controller)
{
	if (!Controller || !InventoryWidget)
		return;
	
	InventoryWidget->RemoveFromViewport();
	InventoryWidget = nullptr;
}

bool UInventoryManagerComponent::IsInventoryUIOpen()
{
	if (!InventoryWidget)
		return false;

	return InventoryWidget->IsInViewport();	
}

