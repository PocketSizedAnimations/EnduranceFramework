// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Tasks/BTTask_SetState.h"
#include "AIController.h"
#include "Components/AIBehaviorCompoment.h"
#include "States/AIState.h"

UBTTask_SetState::UBTTask_SetState()
{
	NodeName = "Set State: None";
}

void UBTTask_SetState::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTTask_SetState, State))
	{
		FString StateName = "None";
		if (State)
			StateName = State->GetClass()->GetDisplayNameText().ToString();

		NodeName = "Set State: " + StateName;
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

EBTNodeResult::Type UBTTask_SetState::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));

	if (BehaviorComponent)
	{
		if (State != nullptr)
			BehaviorComponent->SetState(State);
		else
			BehaviorComponent->ClearState();

		return EBTNodeResult::Succeeded;
	}

	return EBTNodeResult::Failed;
}
