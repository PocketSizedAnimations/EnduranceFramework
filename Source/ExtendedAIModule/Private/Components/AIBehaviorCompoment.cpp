// Copyright (c) 2022 Pocket Sized Animations


#include "Components/AIBehaviorCompoment.h"

/*ai*/
#include "AIController.h"
#include "GameFramework/Pawn.h"
#include "DataAssets/ThreatEvaluation.h"

/*goals*/
#include "Goals/AIGoal.h"

#include "Components/SensesComponent.h"


// Sets default values for this component's properties
UAIBehaviorCompoment::UAIBehaviorCompoment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;	
}


// Called when the game starts
void UAIBehaviorCompoment::BeginPlay()
{
	Super::BeginPlay();
	
	InitBehaviorTree();
}

void UAIBehaviorCompoment::InitBehaviorTree()
{
	if (APawn* P = Cast<APawn>(GetOwner()))
	{
		if (AAIController* AIC = Cast<AAIController>(P->GetController()))
		{
			AIC->RunBehaviorTree(BehaviorTree);
		}
	}
}

void UAIBehaviorCompoment::InitOwnerSensesComponent()
{
	if (APawn* P = Cast<APawn>(GetOwner()))
	{
		OwnerSensesComponent = Cast<USensesComponent>(P->GetComponentByClass(USensesComponent::StaticClass()));
	}
}


// Called every frame
void UAIBehaviorCompoment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*calculate threats from senses component*/
	if (bCalcThreatsFromSensesComponent)
		CalcThreats();	
}

//====================================================
//=======================STATES=======================
//====================================================

void UAIBehaviorCompoment::SetState(UAIState* NewState)
{
	PreviousState = State;
	State = NewState;
}

UAIState* UAIBehaviorCompoment::GetState()
{
	return State;
}

UAIState* UAIBehaviorCompoment::GetPreviousState()
{
	return PreviousState;
}

void UAIBehaviorCompoment::ClearState()
{	
	State = nullptr;
}

void UAIBehaviorCompoment::ClearPreviousState()
{
	PreviousState = nullptr;
}

//=====================================================
//========================GOALS========================
//=====================================================

void UAIBehaviorCompoment::SetGoal(UAIGoal* NewGoal)
{	
	PreviousGoal = Goal;
	Goal = NewGoal;
}

UAIGoal* UAIBehaviorCompoment::GetGoal()
{
	return Goal;
}

UAIGoal* UAIBehaviorCompoment::GetPreviousGoal()
{
	return PreviousGoal;
}

void UAIBehaviorCompoment::ClearGoal()
{
	if(Goal != nullptr)
		PreviousGoal = Goal;
	
	Goal = nullptr;
}

//=====================================================
//======================AGGRESSION=====================
//=====================================================
float UAIBehaviorCompoment::GetAggressionLevel()
{
	return Aggression;
}

float UAIBehaviorCompoment::GetMaxAggressionLevel()
{
	return MaxAggression;
}

float UAIBehaviorCompoment::GetMinAggressionLevel()
{
	return MinAggression;
}

void UAIBehaviorCompoment::SetAggression(float NewAggression)
{
	Aggression = FMath::Clamp(NewAggression, MinAggression, MaxAggression);
}

float UAIBehaviorCompoment::SetRandomAggressionLevel()
{		
	SetAggression(FMath::RandRange(MinAggression, MaxAggression));	
	return Aggression;
}


//=====================================================
//===================THREAT HANDLING===================
//=====================================================

/*CalcThreats() - Keeps track of active Threats by checking various surroundings such as the DetectedActors of our Owner's SensesComponent (if found)*/
void UAIBehaviorCompoment::CalcThreats()
{
	if (bCalcThreatsFromSensesComponent && GetOwnerSensesComponent())
	{
		for (auto ThreatActor : GetOwnerSensesComponent()->GetDetectedActors())
		{
			/*this actor isn't a known threat - so add it*/
			if (IsThreatKnown(ThreatActor) == false)
			{
				AddThreat(ThreatActor);
			}
		}
	}
}

TArray<class UThreatEvaluation*> UAIBehaviorCompoment::GetActiveThreats()
{
	return Threats;
}


/*loops through the Threats array and checks to see if the threat is found*/
bool UAIBehaviorCompoment::IsThreatKnown(AActor* ThreatActor)
{
	for (auto _threat : Threats)
	{
		if (_threat->Actor == ThreatActor)
			return true;
	}

	return false;
}

void UAIBehaviorCompoment::AddThreat(AActor* ThreatActor)
{
	if (ThreatActor == nullptr)
		return;

	if (IsThreatKnown(ThreatActor))
		return;

	UThreatEvaluation* NewThreat = NewObject<UThreatEvaluation>();
	
	if (NewThreat)
	{
		NewThreat->Actor = ThreatActor;
		NewThreat->Owner = GetOwner();
	}

	Threats.Add(NewThreat);
}





//====================================================
//===================ENEMY HANDLING===================
//====================================================

void UAIBehaviorCompoment::SetCurrentEnemy(AActor* NewEnemy)
{
	PreviousEnemy = CurrentEnemy;
	CurrentEnemy = NewEnemy;
}

void UAIBehaviorCompoment::ClearEnemy()
{
	PreviousEnemy = CurrentEnemy;
	CurrentEnemy = nullptr;
}

AActor* UAIBehaviorCompoment::GetCurrentEnemy()
{
	return CurrentEnemy;
}

AActor* UAIBehaviorCompoment::GetPreviousEnemy()
{
	return PreviousEnemy;
}

USensesComponent* UAIBehaviorCompoment::GetOwnerSensesComponent()
{
	if (OwnerSensesComponent)
		return OwnerSensesComponent;
	else
		InitOwnerSensesComponent();

	return OwnerSensesComponent;
}

