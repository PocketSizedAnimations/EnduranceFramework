// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTTask_SetGoal.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTTask_SetGoal : public UBTTaskNode
{
	GENERATED_BODY()
public:

	/*UPROPERTY(EditAnywhere, Category = "Goals")
		bool bSetAsSecondaryGoal;*/
	UPROPERTY(EditAnywhere, Category = "Goals", Instanced)
		class UAIGoal* Goal;
	
	UBTTask_SetGoal();

	virtual void PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent) override;

	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


	/*UPROPERTY(EditAnywhere, Category = "Goals")
		TSubclassOf<UAIGoal> GoalSubclass;

	UPROPERTY(EditAnywhere, Category = "Goals")
		class UAIGoal_DataAsset* DataAsset;
	UPROPERTY(EditAnywhere, Category = "Goals")
		TSubclassOf<class UAIGoal_DataAsset> DataAssetSubclass;*/
};
