// Copyright (c) 2022 Pocket Sized Animations
/* A Muator is a basic class designed to hook into a MutatableComponent allowing you modify native-game existing objects. This class is for extending, modifying, tweaking, etc
* Use a Mod instead if you're looking to add custom classes, new maps, perform a total conversion, etc
*
*
*/

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Mutator.generated.h"

/**
 * 
 */
UCLASS()
class MODMANAGEMENTMODULE_API AMutator : public AInfo
{
	GENERATED_BODY()
	
};
