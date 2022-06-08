// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent), HideCategories = (Sockets, ComponentTick, ComponentReplication, Activation, Cooking, Collision, AssetUserData))
class INVENTORYMODULE_API UInventoryManagerComponent : public UActorComponent
{
	friend class UInventoryItemComponent;

	GENERATED_BODY()
public:

protected:
	UPROPERTY(EditDefaultsOnly)
		bool bCanEquipItems = false;
	/*what's currently active for this manager*/
	UPROPERTY()
		AActor* CurrentlyEquipped;
private:
	/*used to track an item that wants to be equipped but waiting on an action to complete*/
	UPROPERTY()
		AActor* PendingEquip;
protected:
	UPROPERTY(EditAnywhere, meta = (MustImplement="InventoryItemInterface"))
		TArray<TSubclassOf<AActor>> DefaultItems;
protected:
	UPROPERTY()
		TArray<AActor*> Inventory;


	/*ui*/
	UPROPERTY(EditAnywhere, meta = (DisplayName="Inventory UI Class"))
		TSubclassOf<class UInventoryContainerWidget> InventoryUIClass;
	/*ui-reference*/
	UPROPERTY()
		UInventoryContainerWidget* InventoryWidget;

		//===================================================================================================
		//=============================================FUNCTIONS=============================================
		//===================================================================================================

public:	
	// Sets default values for this component's properties
	UInventoryManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = "Spawning")
		virtual void SpawnInventoryFromTemplate(class UInventoryTemplate* InventoryTemplate, bool bClearExisting = true);
	UFUNCTION()
		virtual void SpawnDefaultInventory();
	UFUNCTION(BlueprintCallable, Category = "Spawning")
		virtual void SpawnInventory(TArray<TSubclassOf<AActor>> Items, bool bClearExisting = true);
	UFUNCTION()
		virtual void ClearInventory();


	//=====================================
	//==============EQUIPPING==============
	//=====================================
public:
	UFUNCTION(BlueprintCallable)
		virtual void Equip(AActor* Item);
protected:
	UFUNCTION()
		virtual void OnEquipFinished(AActor* Item);
public:
	UFUNCTION(BlueprintCallable)
		virtual void Unequip(AActor* Item);
protected:
	UFUNCTION()
		virtual void OnUnequipFinished(AActor* Item);

	UFUNCTION()
		virtual bool ShouldAutoEquip(AActor* Item);

	//=======================================
	//============ITEM MANAGEMENT============
	//=======================================
public:
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



protected:
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
