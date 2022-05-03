// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryItemComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnInventorySpawned, AActor*, Item, UInventoryItemComponent*, ItemComponent, UInventoryManagerComponent*, InventoryManager, AActor*, OwningActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnEquipped, AActor*, Item, UInventoryItemComponent*, ItemComponent, UInventoryManagerComponent*, InventoryManager, AActor*, OwningActor);

UENUM()
enum class EEquipCompletionLogic : uint8
{
	Instant,
	Delayed,
	WaitForNotification
};

UCLASS( ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent), HideCategories=(Sockets,ComponentTick,ComponentReplication,Activation,Cooking,Collision,AssetUserData))
class INVENTORYMODULE_API UInventoryItemComponent : public UActorComponent
{
	friend class UInventoryManagerComponent;

	GENERATED_BODY()
public:

private:
	UPROPERTY()
		class UInventoryManagerComponent* InventoryManager;
private:
	UPROPERTY(EditDefaultsOnly)
		EEquipCompletionLogic EquipLogic;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "EquipLogic == EEquipCompletionLogic::Delayed"))
		float EquipDelay = 3.0f;
	UPROPERTY(EditDefaultsOnly)
		EEquipCompletionLogic UnequipLogic;
	UPROPERTY(EditDefaultsOnly, meta = (EditCondition = "UnEquipLogic == EEquipCompletionLogic::Delayed"))
		float UnequipDelay = 3.0f;

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

public:	
	// Sets default values for this component's properties
	UInventoryItemComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

private:
	UFUNCTION()
		virtual void OnEquipped();
	UFUNCTION()
		virtual void OnEquippedFinished();
private:
	UFUNCTION()
		virtual void BeginEquip();
	UFUNCTION()
		virtual void EndEquip();

public:
	UFUNCTION(BlueprintPure)
		class UInventoryManagerComponent* GetInventoryManager() { return InventoryManager; };
		
private:
	UFUNCTION()
		virtual void EnableCollision();
	UFUNCTION()
		virtual void DisableCollision();
	UFUNCTION()
		virtual void EnableVisibility();
	UFUNCTION()
		virtual void DisableVisibility();
};
