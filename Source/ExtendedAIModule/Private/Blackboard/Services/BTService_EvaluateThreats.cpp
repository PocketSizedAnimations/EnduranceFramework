// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Services/BTService_EvaluateThreats.h"

UBTService_EvaluateThreats::UBTService_EvaluateThreats()
{
	NodeName = "Evaluate Threats";
}

void UBTService_EvaluateThreats::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);


}

void UBTService_EvaluateThreats::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}


void UBTService_EvaluateThreats::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}
