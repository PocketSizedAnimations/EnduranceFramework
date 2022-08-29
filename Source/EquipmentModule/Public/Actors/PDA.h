// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment.h"
#include "PDA.generated.h"

/**
 * 
 */
UCLASS(abstract)
class EQUIPMENTMODULE_API APDA : public AEquipment
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
