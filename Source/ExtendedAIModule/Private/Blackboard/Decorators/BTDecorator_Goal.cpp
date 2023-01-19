// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_Goal.h"
#include "Goals/AIGoal.h"
#include "AIController.h"
#include "Components/AIBehaviorCompoment.h"

UBTDecorator_Goal::UBTDecorator_Goal()
{
	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;
	bCreateNodeInstance = false;

	NodeName = "Goal: None";
}

void UBTDecorator_Goal::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_Goal, Goal))
	{
		if (Goal)
		{			
			NodeName = "Goal: " + Goal->GetDisplayNameText().ToString();
			//Goal.GetDefaultObject()->DisplayName;
		}
		else
		{
			NodeName = "Goal: None";
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UBTDecorator_Goal::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

bool UBTDecorator_Goal::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
		return false;

	if (UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass())))
	{
		if (BehaviorComponent->GetGoal() == nullptr && Goal == nullptr)
			return true;
		else if (BehaviorComponent->GetGoal() && (BehaviorComponent->GetGoal()->IsA(Goal)))
			return true;		
		else
			return false;
	}

	return false;
}
