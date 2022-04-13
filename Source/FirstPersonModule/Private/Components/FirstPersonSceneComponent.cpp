// Copyright (c) 2022 Pocket Sized Animations


#include "Components/FirstPersonSceneComponent.h"

// Sets default values for this component's properties
UFirstPersonSceneComponent::UFirstPersonSceneComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UFirstPersonSceneComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFirstPersonSceneComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);


	/*match controller rotation*/
	if (bFreeLooking == false) //stop updating while we're in free look mode
	{
		if (APawn* P = Cast<APawn>(GetOwner()))
		{
			if (AController* C = P->GetController())
			{
				SetRelativeRotation(FRotator(C->GetControlRotation().Pitch, 0, 0));
			}
		}
	}
}

