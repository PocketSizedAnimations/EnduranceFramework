// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_HasDetectedActors.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/SensesComponent.h"
#include "BehaviorTree/BlackboardComponent.h"

#include "BehaviorTree/Blackboard/BlackboardKeyType_Object.h"



UBTDecorator_HasDetectedActors::UBTDecorator_HasDetectedActors()
{
	NodeName = "Has Detected Actor";
	FlowAbortMode = EBTFlowAbortMode::Both;
	bNotifyTick = true;
	bLastValue = false;
	bCreateNodeInstance = false;

	ActorToCheck.AddObjectFilter(this, GET_MEMBER_NAME_CHECKED(UBTDecorator_HasDetectedActors, ActorToCheck), AActor::StaticClass());
	ActorToCheck.SelectedKeyName = FBlackboard::KeySelf;

	ClassFilter = AActor::StaticClass();
}

void UBTDecorator_HasDetectedActors::TickNode(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory, float DeltaSeconds)
{
	if (CheckForDetectedActors(OwnerComp, NodeMemory) != bLastValue)
	{
		bLastValue = !bLastValue;		
		OwnerComp.RequestExecution(this);
	}	
}

bool UBTDecorator_HasDetectedActors::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	return CheckForDetectedActors(OwnerComp, NodeMemory);
}

bool UBTDecorator_HasDetectedActors::CheckForDetectedActors(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AExtendedAIController* AIController = Cast<AExtendedAIController>(OwnerComp.GetAIOwner());

	if (!AIController || !AIController->GetPawn())
		return false;

	/*find SensesComponent*/
	if (USensesComponent* SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass())))
	{
		if (bAnyActor)
			return SensesComponent->HasDetectedAnyActors(ClassFilter);
		else
		{			
			const UBlackboardComponent* OwningBlackboard = OwnerComp.GetBlackboardComponent();
			UObject* KeyValue = OwningBlackboard->GetValue<UBlackboardKeyType_Object>(ActorToCheck.GetSelectedKeyID());
			AActor* TargetActor = Cast<AActor>(KeyValue);

			/*checks to make sure Blackboard Key value is the proper filter type - and that it's been detected*/
			if (TargetActor && TargetActor->IsA(ClassFilter))
				return SensesComponent->HasDetected(TargetActor);
			else
				return false;
		}
	}

	return false;
}
