// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Tasks/BTTask_SetAggression.h"
#include "Controllers/ExtendedAIController.h"
#include "Components/AIBehaviorCompoment.h"

UBTTask_SetAggression::UBTTask_SetAggression()
{
	NodeName = "Increase Aggression by 50%";
}


void UBTTask_SetAggression::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{
	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UBTTask_SetAggression, AggressionModifier) || PropertyName == GET_MEMBER_NAME_CHECKED(UBTTask_SetAggression, AggressionLevel))
	{
		FString AggroModifierString;
		FString AggroLevelString = FString::SanitizeFloat(AggressionLevel);

		if (AggressionModifier == ESetAggressionType::Set)
			AggroModifierString = "Set Aggression To";
		else if (AggressionModifier == ESetAggressionType::Increase)
			AggroModifierString = "Increase Aggression by";
		else if (AggressionModifier == ESetAggressionType::Decrease)
			AggroModifierString = "Decrease Aggression by";

		NodeName = AggroModifierString + " " + AggroLevelString + "%";
	}

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

EBTNodeResult::Type UBTTask_SetAggression::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AAIController* AIController = OwnerComp.GetAIOwner();
	UAIBehaviorCompoment* BehaviorComponent = Cast<UAIBehaviorCompoment>(AIController->GetPawn()->GetComponentByClass(UAIBehaviorCompoment::StaticClass()));

	if (AIController && BehaviorComponent)
	{
		if (AggressionModifier == ESetAggressionType::Set)
			BehaviorComponent->SetAggression(AggressionLevel);
		else if (AggressionModifier == ESetAggressionType::Increase)
			BehaviorComponent->SetAggression(BehaviorComponent->GetAggressionLevel() + AggressionLevel);
		else if (AggressionModifier == ESetAggressionType::Decrease)
			BehaviorComponent->SetAggression(BehaviorComponent->GetAggressionLevel() - AggressionLevel);

		return EBTNodeResult::Succeeded;
	}

	
	return EBTNodeResult::Failed;

}