// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "InventoryManagerComponent.generated.h"


UCLASS( ClassGroup=(Inventory), meta=(BlueprintSpawnableComponent), HideCategories = (Sockets, ComponentTick, ComponentReplication, Activation, Cooking, Collision, AssetUserData))
class INVENTORYMODULE_API UInventoryManagerComponent : public UActorComponent
{
	GENERATED_BODY()
public:

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


	UFUNCTION()
		virtual void SpawnDefaultInventory();
	UFUNCTION()
		virtual void SpawnInventory(TArray<TSubclassOf<AActor>> Items, bool bRemoveExisting = true);
	UFUNCTION()
		virtual void ClearInventory();

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
