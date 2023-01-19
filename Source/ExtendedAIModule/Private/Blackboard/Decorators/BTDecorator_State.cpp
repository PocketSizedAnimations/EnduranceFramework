// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_State.h"
#include "States/AIState.h"
#include "AIController.h"
#include "Components/AIBehaviorCompoment.h"

UBTDecorator_State::UBTDecorator_State()
{
	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;

	NodeName = "State: None";
}


void UBTDecorator_State::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTDecorator_State, State))
	{
		if (State)
		{
			NodeName = "State: " + State->GetDisplayNameText().ToString();
			//Goal.GetDefaultObject()->DisplayName;
		}
		else
		{
			NodeName = "State: None";
		}
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}


void UBTDecorator_State::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{

}

bool UBTDecorator_State::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{

	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
		return false;

	if (UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass())))
	{
		if (BehaviorComponent->GetState() == nullptr && State == nullptr)
			return true;
		else if (BehaviorComponent->GetState() && (BehaviorComponent->GetState()->IsA(State)))
			return true;
		else
			return false;
	}

	return false;
}
