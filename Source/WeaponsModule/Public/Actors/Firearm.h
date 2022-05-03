// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"

#include "Firearm.generated.h"


/**
 * 
 */
UCLASS(abstract)
class WEAPONSMODULE_API AFirearm : public AWeapon
{
	GENERATED_BODY()
public:



	//=====================================================================================
	//=====================================FUNCTIONS=======================================
	//=====================================================================================
	AFirearm(const FObjectInitializer& ObjectInitializer);




	
};
