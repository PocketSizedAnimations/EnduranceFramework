// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_ThreeParams(FOnItemAdded, UInventoryManagerComponent*, InventoryManager, AActor*, OwningActor, AActor*, InventoryItem);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemEquipped, AActor*, Item);

UENUM(BlueprintType)
enum class EQuickslot : uint8
{
	Quickslot1,
	Quickslot2,
	Quickslot3,
	Quickslot4,
	Quickslot5,
	Quickslot6,
	Quickslot7,
	Quickslot8,
	Quickslot9,
	Quickslot10
};


UCLASS( ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent), HideCategories = (Sockets, ComponentTick, ComponentReplication, Activation, Cooking, Collision, AssetUserData))
class INVENTORYMODULE_API UInventoryManagerComponent : public UActorComponent
{
	friend class UInventoryItemComponent;

	GENERATED_BODY()
public:


protected:
	/*what's currently active for this manager*/
	UPROPERTY(Replicated)
		AActor* CurrentlyEquipped;
	UPROPERTY(Replicated)
		AActor* PrimaryWeapon;
	UPROPERTY(Replicated)
		AActor* AlternativeWeapon;
	UPROPERTY(Replicated)
		AActor* SecondaryWeapon;
private:
	/*used to track an item that wants to be equipped but waiting on an action to complete*/
	UPROPERTY()
		AActor* PendingEquip;
protected:
	/*Primary Weapon - must implement PrimaryWeaponInterface*/
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "bEnablePrimaryWeapon", EditConditionHides, MustImplement = "PrimaryWeaponInterface", DisplayName = "Primary Weapon"))
		TSubclassOf<AActor> DefaultPrimary;
	/*Primary Weapon - must implement SecondaryWeaponInterface*/
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "bEnableSecondaryWeapon", EditConditionHides, MustImplement = "SecondaryWeaponInterface", DisplayName = "Secondary Weapon"))
		TSubclassOf<AActor> DefaultSecondary;
	/*Primary Weapon - must implement AlternativeWeaponInterface*/
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (EditCondition = "bEnableAlternativeWeapon", EditConditionHides, MustImplement = "AlternativeWeaponInterface", DisplayName = "Alternative Weapon"))
		TSubclassOf<AActor> DefaultAlternative;
	UPROPERTY(EditAnywhere, Category = "Inventory", meta = (MustImplement="InventoryItemInterface", DisplayName = "Inventory"))
		TArray<TSubclassOf<AActor>> DefaultItems;


protected:
	UPROPERTY(Replicated)
		TArray<AActor*> Inventory;

	UPROPERTY()
		TArray<AActor*> Quickslots;


protected:
	UPROPERTY(EditDefaultsOnly, Category = "Configuration")
		bool bCanEquipItems;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Primary", meta = (EditCondition="bCanEquipItems"))
		bool bEnablePrimaryWeapon;
	/*automatically equips Primary as the CurrentWeapon during initial spawning*/
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Primary", meta = (EditConditino = "bEnablePrimaryWeapon"))
		bool bAutoEquipPrimaryOnSpawn;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Secondary", meta = (EditCondition = "bCanEquipItems"))
		bool bEnableSecondaryWeapon;
	UPROPERTY(EditDefaultsOnly, Category = "Configuration|Alternative", meta = (EditCondition = "bCanEquipItems"))
		bool bEnableAlternativeWeapon;

protected:
	/*ui*/
	UPROPERTY(EditAnywhere, meta = (DisplayName="Inventory UI Class"))
		TSubclassOf<class UInventoryContainerWidget> InventoryUIClass;
	/*ui-reference*/
	UPROPERTY()
		UInventoryContainerWidget* InventoryWidget;

public:
	/*event/delegates*/
	UPROPERTY(BlueprintAssignable)
		FOnItemEquipped OnItemEquipped;
	UPROPERTY(BlueprintAssignable)
		FOnItemEquipped OnPrimaryEquipped;
	UPROPERTY(BlueprintAssignable)
		FOnItemEquipped OnSecondaryEquipped;
	UPROPERTY(BlueprintAssignable)
		FOnItemEquipped OnAlternativeEquipped;
	UPROPERTY(BlueprintAssignable)
		FOnItemAdded OnItemAdded;
	UPROPERTY(BlueprintAssignable)
		FOnItemAdded OnPrimaryAssigned;
	UPROPERTY(BlueprintAssignable)
		FOnItemAdded OnSecondaryAssigned;
	UPROPERTY(BlueprintAssignable)
		FOnItemAdded OnAlternativeAssigned;

		//===================================================================================================
		//=============================================FUNCTIONS=============================================
		//===================================================================================================

public:	
	// Sets default values for this component's properties
	UInventoryManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	//=====================================
	//==============INVENTORY==============
	//=====================================
public:
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		virtual void SpawnInventoryFromTemplate(class UInventoryTemplate* InventoryTemplate, bool bClearExisting = true);
protected:
	UFUNCTION()
		virtual void SpawnDefaultInventory();
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		virtual void SpawnInventory(TArray<TSubclassOf<AActor>> Items, bool bClearExisting = true);
	UFUNCTION()
		virtual AActor* SpawnInventoryItem(TSubclassOf<AActor> ItemClass);
public:
	UFUNCTION()
		virtual void ClearInventory();
public:
	UFUNCTION(BlueprintPure, Category = "Inventory")
		AActor* GetCurrentlyEquippedItem();



	//=====================================
	//==============EQUIPPING==============
	//=====================================
public:
	UFUNCTION(BlueprintCallable, Category = "Equipping/Unequipping")
		virtual void Equip(AActor* Item);
protected:
	UFUNCTION()
		virtual void OnEquipFinished(AActor* Item);
public:
	UFUNCTION(BlueprintCallable, Category = "Equipping/Unequipping")
		virtual void Unequip(AActor* Item);
protected:
	UFUNCTION()
		virtual void OnUnequipFinished(AActor* Item);

	UFUNCTION()
		virtual bool ShouldAutoEquip(AActor* Item);

	//====================================
	//=============QUICKSLOTS=============
	//====================================

public:
	UFUNCTION(BlueprintPure, Category = "Quickslots")
		virtual AActor* GetPrimaryWeapon();
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void AssignPrimaryWeapon(AActor* Weapon);
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void EquipPrimaryWeapon();
	UFUNCTION(BlueprintPure, Category = "Quickslots")
		virtual AActor* GetSecondaryWeapon();
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void AssignSecondaryWeapon(AActor* Weapon);
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void EquipSecondaryWeapon();
	UFUNCTION(BlueprintPure, Category = "Quickslots")
		virtual AActor* GetAlternativeWeapon();
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void AssignAlternativeWeapon(AActor* Weapon);
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void EquipAlternativeWeapon();

	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void AssignToQuickslot(AActor* ActorToAssign, EQuickslot Quickslot);
	UFUNCTION(BlueprintCallable, Category = "Quickslots")
		virtual void EquipQuickslot(EQuickslot Quickslot);
	UFUNCTION(BlueprintCallable, BlueprintPure, Category = "Quickslots")
		virtual AActor* GetQuickslotItem(EQuickslot Quickslot);

	//=======================================
	//============ITEM MANAGEMENT============
	//=======================================
public:
	/*returns a copy of the inventory (in-order) - however any modifications to this will not affect the actual Inventory within the Manager for safety reasons*/
	UFUNCTION(BlueprintPure)
		TArray<AActor*> GetInventory() { return Inventory; };
	UFUNCTION(BlueprintPure)
		bool ContainsItem(AActor* Item);
	UFUNCTION(BlueprintCallable)
		bool AddItem(AActor* Item);
	UFUNCTION(BlueprintCallable)
		bool RemoveItem(AActor* Item);
	UFUNCTION(BlueprintCallable)
		void DropItem(AActor* Item);

private:	
	UFUNCTION(BlueprintCallable)
		void StoreItem(AActor* Item);
	UFUNCTION()
		void RegisterItem(AActor* Item);



public:
	UFUNCTION(BlueprintPure)
		virtual UInventoryItemComponent* GetItemComponent(AActor* Item);

	//==============================
	//==============UI==============
	//==============================
public:
	UFUNCTION(BlueprintCallable)
		virtual void OpenInventoryUI(class APlayerController* Controller);
	UFUNCTION(BlueprintCallable)
		virtual void CloseInventoryUI(class APlayerController* Controller);
	UFUNCTION(BlueprintPure, meta=(DisplayName="Is Inventory UI Open"))
		virtual bool IsInventoryUIOpen();
};
