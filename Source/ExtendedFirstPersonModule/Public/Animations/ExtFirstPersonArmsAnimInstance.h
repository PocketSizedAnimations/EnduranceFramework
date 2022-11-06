// Copyright (c) 2022 Pocket Sized Animations
/* Extended First Person Anim Instance - this version simply relies (depends on) various other Endurance Modules so it's been separated so you aren't forced to use all the
* other dependant modules (InventoryModule, WeaponsModule, etc) if you don't want to.
*
*
*
*/

#pragma once

#include "CoreMinimal.h"
#include "Animations/FirstPersonArmsAnimInstance.h"
#include "ExtFirstPersonArmsAnimInstance.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDFIRSTPERSONMODULE_API UExtFirstPersonArmsAnimInstance : public UFirstPersonArmsAnimInstance
{
	GENERATED_BODY()
public:



	/*inventory*/
	UPROPERTY()
		class UInventoryManagerComponent* InventoryManager;

	//=======================================================================================================================================================
	//=======================================================================FUNCTIONS=======================================================================
	//=======================================================================================================================================================

	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;
		


	//=====================================================
	//=======================INVENTORY=====================
	//=====================================================
	virtual void OnUpdateItemStates() override;
	virtual void UpdateCurrentlyEquippedItem() override;
	virtual void UpdateItemEquipState() override;	
	UFUNCTION(BlueprintPure)
		bool HasWeaponEquipped();
	UFUNCTION(BlueprintPure)
		bool HasPDAEquipped();
	UFUNCTION(BlueprintPure)
		class UInventoryManagerComponent* GetInventoryManager();
	UFUNCTION(BlueprintPure)
		class UInventoryItemComponent* GetCurrentItemComponent();

};
