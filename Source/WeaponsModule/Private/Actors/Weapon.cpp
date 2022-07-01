// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/Weapon.h"

#include "InventoryModule/Public/Components/InventoryItemComponent.h"


// Sets default values
AWeapon::AWeapon(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Mesh = ObjectInitializer.CreateDefaultSubobject<USkeletalMeshComponent>(this, TEXT("MeshComp"));
	if (Mesh)
	{
		SetRootComponent(Mesh);
	}
	
	ItemComponent = ObjectInitializer.CreateDefaultSubobject<UInventoryItemComponent>(this, TEXT("ItemComp"));
	AddOwnedComponent(ItemComponent);
	if (ItemComponent)
	{	
		ItemComponent->OnEquipBegin.AddDynamic(this, &AWeapon::OnEquipBegin);
	}

	bReplicates = true;
	NetPriority = 3.0f; //similar to PlayerController
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AWeapon::BeginFire()
{

}

void AWeapon::EndFire()
{

}

void AWeapon::OnEquipBegin(AActor* Actor, UInventoryItemComponent* ItemComp, UInventoryManagerComponent* InvManager, AActor* Equipper)
{

}

