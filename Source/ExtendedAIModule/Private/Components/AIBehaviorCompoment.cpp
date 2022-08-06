// Copyright (c) 2022 Pocket Sized Animations


#include "Components/AIBehaviorCompoment.h"

// Sets default values for this component's properties
UAIBehaviorCompoment::UAIBehaviorCompoment()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAIBehaviorCompoment::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAIBehaviorCompoment::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

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

