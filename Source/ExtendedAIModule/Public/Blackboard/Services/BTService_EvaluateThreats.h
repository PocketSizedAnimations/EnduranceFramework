// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/Services/BTService_BlackboardBase.h"
#include "BTService_EvaluateThreats.generated.h"

/**
 * 
 */
UCLASS()
class EXTENDEDAIMODULE_API UBTService_EvaluateThreats : public UBTService_BlackboardBase
{
	GENERATED_BODY()
public:



	UBTService_EvaluateThreats();	
	virtual void TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds) override;
	virtual void OnSearchStart(FBehaviorTreeSearchData& SearchData);
	virtual void OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;

};
