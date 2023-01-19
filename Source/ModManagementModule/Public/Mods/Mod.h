// Copyright (c) 2022 Pocket Sized Animations
/* A Mod is a class that can get loaded into the ModSubsystem and then brought to life in order to add new classes, new weapons, new maps and modes, and etc.
* if you're looking to modify existing native classes, look into using a Mutator - which is designed to easily modify existing classes.
*
*
*
*/
#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Info.h"
#include "Mod.generated.h"

/**
 * 
 */
UCLASS(Blueprintable)
class MODMANAGEMENTMODULE_API AMod : public AInfo
{
	GENERATED_BODY()
public:
};
