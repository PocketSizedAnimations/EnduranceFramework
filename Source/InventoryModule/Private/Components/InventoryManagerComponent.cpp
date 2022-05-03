// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InventoryManagerComponent.h"
#include "Components/InventoryItemComponent.h"
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

void UInventoryManagerComponent::SpawnDefaultInventory()
{
	/*safety check*/
	if (GetNetMode() == NM_Client) 
		return;

	SpawnInventory(DefaultItems, true);
}

void UInventoryManagerComponent::SpawnInventory(TArray<TSubclassOf<AActor>> Items, bool bRemoveExisting)
{
	/*server-check*/
	if (GetOwner() == nullptr || GetOwner()->GetNetMode() == NM_Client)
		return;
	
	/*destroy existing inventory*/
	if (bRemoveExisting)
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

	for (TSubclassOf<AActor> ItemClass : Items)
	{		
		AActor* Item = GetWorld()->SpawnActor<AActor>(ItemClass, SpawnTransform, SpawnParams);
		if (Item)
		{
			if (UInventoryItemComponent* ItemComp = Cast<UInventoryItemComponent>(Item->GetComponentByClass(UInventoryItemComponent::StaticClass())))
			{				
				AddItem(ItemComp->GetOwner());
			}
		}
	}
}

void UInventoryManagerComponent::ClearInventory()
{

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

