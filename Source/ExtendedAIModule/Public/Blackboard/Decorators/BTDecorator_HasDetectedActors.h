// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Decorators/BTDecorator_BlackboardBase.h"
#include "BTDecorator_HasDetectedActors.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTDecorator_HasDetectedActors : public UBTDecorator_BlackboardBase
{
	GENERATED_BODY()
public:


	UBTDecorator_HasDetectedActors();
	


	bool CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const override;

};
