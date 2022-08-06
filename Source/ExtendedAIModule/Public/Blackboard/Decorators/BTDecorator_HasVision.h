// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_HasVision.generated.h"

/**
 * 
 */
UCLASS(HideCategories="Blackboard")
class EXTENDEDAIMODULE_API UBTDecorator_HasVision : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:

	
	UBTDecorator_HasVision(const FObjectInitializer& ObjectInitializer);

	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;
};
