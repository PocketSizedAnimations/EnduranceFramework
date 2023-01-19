// Copyright (c) 2022 Pocket Sized Animations


#include "Blackboard/Decorators/BTDecorator_HeardSound.h"
#include "AIController.h"
#include "Components/SensesComponent.h"
#include "AudibleModule/Public/Subsystems/AudioSubsystem.h"



UBTDecorator_HeardSound::UBTDecorator_HeardSound()
{
	FlowAbortMode = EBTFlowAbortMode::None;
	bAllowAbortChildNodes = false;
	bAllowAbortLowerPri = false;
	bAllowAbortNone = true;
	NodeName = "Heard Sound";
}

bool UBTDecorator_HeardSound::CalculateRawConditionValue(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) const
{
	AAIController* AIController = OwnerComp.GetAIOwner();

	if (!AIController || !AIController->GetPawn())
		return false;

	/*find SensesComponent*/
	if (USensesComponent* SensesComponent = Cast<USensesComponent>(AIController->GetPawn()->GetComponentByClass(USensesComponent::StaticClass())))
	{
		return SensesComponent->HeardNoise();
	}

	return false;
}

FString UBTDecorator_HeardSound::GetStaticDescription() const
{
	FString CategoryString;
	switch (Category)
	{
	case ESoundCategory::Environmental:
		CategoryString = "Environmental";
		break;
	case ESoundCategory::EnvironmentalDisturbance:
		CategoryString = "Environmental Disturbance";
		break;
	case ESoundCategory::Footsteps:
		CategoryString = "Footsteps";
		break;
	case ESoundCategory::WeaponFoley:
		CategoryString = "Weapon Foley";
		break;
	case ESoundCategory::Gunshot:
		CategoryString = "Gunshot";
		break;
	case ESoundCategory::Explosion:
		CategoryString = "Explosion";
		break;
	default: 
		CategoryString = "Unknown";
		break;
	}
		
	
	if (bFilterByCategory && bFilterByDistance)
		return FString::Printf(TEXT("%s: Category: %s, Distance: %f"), *Super::GetStaticDescription(), *CategoryString, MaxDistance);
	else if (bFilterByCategory && !bFilterByDistance)
		return FString::Printf(TEXT("%s: Category: %s"), *Super::GetStaticDescription(), *CategoryString);
	else if (!bFilterByCategory && bFilterByDistance)
		return FString::Printf(TEXT("%s: Distance: %f"), *Super::GetStaticDescription(), MaxDistance);
	else
		return *Super::GetStaticDescription();

}
