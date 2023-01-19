// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_MoveToNextPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTTask_MoveToNextPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
public:


	UBTTask_MoveToNextPatrolPoint();
	
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
