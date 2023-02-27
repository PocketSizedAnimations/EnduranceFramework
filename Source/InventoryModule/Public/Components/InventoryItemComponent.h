// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnInventorySpawned, AActor*, Item, UInventoryItemComponent*, ItemComponent, UInventoryManagerComponent*, InventoryManager, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEquipped, AActor*, Item, UInventoryItemComponent*, ItemComponent, UInventoryManagerComponent*, InventoryManager, AActor*, OwningActor);

UENUM(BlueprintType)
enum class EEquipCompletionLogic : uint8
{
	Instant,
	Delayed,
	WaitForNotification
};

UENUM(BlueprintType)
enum class EEquipState : uint8 {
	NONE,
	InStorage,
	Equipping,
	Unequipping,
	Equipped
};

UCLASS( ClassGroup=(Inventory), AutoExpandCategories=("Equipping/Unequipping|Equipping"), meta = (BlueprintSpawnableComponent), HideCategories = (Sockets, ComponentTick, ComponentReplication, Activation, Cooking, Collision, AssetUserData))
class INVENTORYMODULE_API UInventoryItemComponent : public UActorComponent
{
	friend class UInventoryManagerComponent;

	GENERATED_BODY()
public:

private:
	UPROPERTY()
		class UInventoryManagerComponent* InventoryManager;
private:
	/*automatically equips this item when picked up or spawned into inventory*/
	UPROPERTY(EditAnywhere, Category = "Equipping/Unequipping")
		bool bAutoEquip = false;
	UPROPERTY(EditDefaultsOnly, Category = "Equipping/Unequipping")
		uint8 EquipPriority = 0;
	UPROPERTY()
		EEquipState EquipState = EEquipState::NONE;
	
	FTimerHandle EquipHandler;
	UPROPERTY(EditDefaultsOnly, Category = "Equipping/Unequipping|Equipping")
		EEquipCompletionLogic EquipLogic;
	UPROPERTY(EditDefaultsOnly, Category = "Equipping/Unequipping|Equipping", meta = (EditCondition = "EquipLogic == EEquipCompletionLogic::Delayed"))
		float EquipDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Equipping/Unequipping|Equipping", meta = (AdvancedDisplay))
		TArray<class UItemEvent*> OnEquipEvents;

	FTimerHandle UnequipHandler;
	UPROPERTY(EditDefaultsOnly, Category = "Equipping/Unequipping|Unequipping")
		EEquipCompletionLogic UnequipLogic;
	UPROPERTY(EditDefaultsOnly, Category = "Equipping/Unequipping|Unequipping", meta = (EditCondition = "UnEquipLogic == EEquipCompletionLogic::Delayed"))
		float UnequipDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly, Instanced, Category = "Equipping/Unequipping|Unequipping", meta = (AdvancedDisplay))
		TArray<class UItemEvent*> OnUnequipEvents;

	UPROPERTY(Replicated, ReplicatedUsing = "OnRep_CollisionChanged")
		bool bCollisionEnabled = true;


public:
	UPROPERTY(BlueprintAssignable)
		FOnInventorySpawned OnItemSpawned;
	UPROPERTY(BlueprintAssignable)
		FOnEquipped OnEquipBegin;
	UPROPERTY(BlueprintAssignable)
		FOnEquipped OnEquipEnd;
	UPROPERTY(BlueprintAssignable)
		FOnEquipped OnUnequipBegin;
	UPROPERTY(BlueprintAssignable)
		FOnEquipped OnUnequipEnd;

	//===========================================================================================================================================================
	//=========================================================================FUNCTIONS=========================================================================
	//===========================================================================================================================================================

public:	
	// Sets default values for this component's properties
	UInventoryItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	UFUNCTION(BlueprintPure, Category = "State")
		EEquipState GetEquipState() { return EquipState; };

private:
	UFUNCTION()
		virtual void BeginEquip();
	UFUNCTION()
		virtual void EndEquip();
	UFUNCTION()
		virtual void BeginUnequip();
	UFUNCTION()
		virtual void EndUnequip();

public:
	UFUNCTION(BlueprintPure)
		class UInventoryManagerComponent* GetInventoryManager() { return InventoryManager; };
	UFUNCTION(BlueprintPure)
		class AActor* GetOwningActor();

		
private:
	UFUNCTION()
		virtual void EnableCollision();
	UFUNCTION()
		virtual void DisableCollision();
	UFUNCTION()
		virtual void OnRep_CollisionChanged();
	UFUNCTION()
		virtual void EnableVisibility();
	UFUNCTION()
		virtual void DisableVisibility();
};
