// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/ElectronicDevice.h"
#include "PDA.generated.h"

/**
 * 
 */
UCLASS(abstract)
class EQUIPMENTMODULE_API APDA : public AElectronicDevice
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleDefaultsOnly)
		class USkeletalMeshComponent* Mesh;
	UPROPERTY(VisibleDefaultsOnly)
		class UWidgetComponent* UI;


	//=========================================================================================
	//========================================FUNCTIONS========================================
	//=========================================================================================
public:
	APDA(const FObjectInitializer& ObjectInitializer);
	
};
