// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Tasks/BTTask_SetGoal.h"
#include "Goals/AIGoal.h"
#include "AIController.h"
#include "Components/AIBehaviorCompoment.h"

UBTTask_SetGoal::UBTTask_SetGoal()
{
	NodeName = "Set Goal: None";
}

void UBTTask_SetGoal::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTTask_SetGoal, Goal))
	{
		FString GoalName = "None";
		if (Goal)
			GoalName = Goal->GetClass()->GetDisplayNameText().ToString();

		NodeName = "Set Goal: " + GoalName;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

EBTNodeResult::Type UBTTask_SetGoal::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));

	if (BehaviorComponent)
	{
		if (Goal != nullptr)
			BehaviorComponent->SetGoal(Goal);
		else
			BehaviorComponent->ClearGoal();

		return EBTNodeResult::Succeeded;
	}
	
	return EBTNodeResult::Failed;
}
