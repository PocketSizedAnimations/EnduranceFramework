// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/Equipment.h"
#include "InventoryModule/Public/Components/InventoryItemComponent.h"

// Sets default values
AEquipment::AEquipment(const FObjectInitializer& ObjectInitializer)
{
 	
	ItemComponent = ObjectInitializer.CreateDefaultSubobject<UInventoryItemComponent>(this, TEXT("ItemComp"));
	if (ItemComponent)
	{
		
	}

	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEquipment::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AEquipment::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AEquipment::TurnOn()
{
}

void AEquipment::TurnOff()
{
}

