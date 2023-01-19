// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetAlertLevel.generated.h"

enum class EAlertState : uint8;
/**
 * 
 */
UCLASS(DisplayName="Set Alertness")
class EXTENDEDAIMODULE_API UBTTask_SetAlertLevel : public UBTTaskNode
{
	GENERATED_BODY()
public:


	UPROPERTY(EditAnywhere, Category = "Alert State")
		EAlertState AlertState;



	UBTTask_SetAlertLevel();


	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
