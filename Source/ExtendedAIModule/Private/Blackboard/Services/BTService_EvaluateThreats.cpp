// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Services/BTService_EvaluateThreats.h"

#include "Components/AIBehaviorCompoment.h"
#include "DataAssets/ThreatEvaluation.h"
#include "AIController.h"




UBTService_EvaluateThreats::UBTService_EvaluateThreats()
{
	NodeName = "Evaluate Threats";
	bNotifyTick = true;
}

void UBTService_EvaluateThreats::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	Super::TickNode(OwnerComp, NodeMemory, DeltaSeconds);
	
	EvaluateThreats(OwnerComp.GetAIOwner());
}

void UBTService_EvaluateThreats::OnSearchStart(FBehaviorTreeSearchData& SearchData)
{
	Super::OnSearchStart(SearchData);
}


void UBTService_EvaluateThreats::OnCeaseRelevant(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	Super::OnCeaseRelevant(OwnerComp, NodeMemory);
}

float UBTService_EvaluateThreats::EvaluateThreats(AAIController* AIController)
{
	/*loop through the threats and score them*/
	for (auto Threat : GetKnownThreats(AIController))
	{
		if (bEvaluateDistance)
			Threat->CalcDistanceScore(MaxDistance,DistanceScore);

	}

	return 0.0f;
}

TArray<UThreatEvaluation*> UBTService_EvaluateThreats::GetKnownThreats(AAIController* AIController)
{	
	if (UAIBehaviorCompoment* BehaviorComp = GetOwnerBehaviorComponent(AIController))
	{
		return BehaviorComp->GetActiveThreats();
	}

	return TArray<UThreatEvaluation*>();
}

UAIBehaviorCompoment* UBTService_EvaluateThreats::GetOwnerBehaviorComponent(AAIController* AIController)
{
	if (BehaviorComponent == nullptr)
	{
		if (!AIController || !AIController->GetPawn())
			BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));
	}	
	return BehaviorComponent;
}

