// Copyright (c) 2022 Pocket Sized Animations


#include "Interactives/Door.h"
#include "Components/InteractiveBoxComponent.h"

#include "Curves/CurveFloat.h"


/*utilities*/
#include "Components/TimelineComponent.h"

// Sets default values
ADoor::ADoor(const FObjectInitializer& ObjectInitializer)
{
	/*replication*/
	bReplicates = true;
	bNetLoadOnClient = true;

	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ADoor::BeginPlay()
{
	Super::BeginPlay();
}



