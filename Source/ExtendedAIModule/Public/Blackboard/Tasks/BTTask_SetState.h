// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetState.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTTask_SetState : public UBTTaskNode
{
	GENERATED_BODY()
public:

	UPROPERTY(EditAnywhere, Category = "State", Instanced)
		class UAIState* State;


	UBTTask_SetState();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;
	
};
