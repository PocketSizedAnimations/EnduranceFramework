// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTDecorator.h"
#include "BTDecorator_RecentlyLostActor.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_RecentlyLostActor : public UBTDecorator
{
	GENERATED_BODY()
public:

	bool bLastValue = false;

	UBTDecorator_RecentlyLostActor();
};
