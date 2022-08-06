// Copyright (c) 2022 Pocket Sized Animations


#include "Components/SensesComponent.h"
#include "GameFramework/GameModeBase.h"
#include "Components/StimuliComponent.h"

USensesComponent::USensesComponent()
{
	PrimaryComponentTick.bCanEverTick = false;
}


void USensesComponent::BeginPlay()
{
	Super::BeginPlay();	


	/*server-initiation*/
	if (GetOwner() && GetNetMode() < NM_Client)
	{
		if (bHasVision)
			GetOwner()->GetWorldTimerManager().SetTimer(VisionUpdateHandler, this, &USensesComponent::OnVisionUpdate, VisionUpdateInterval, true);
	
		if (GetAISubsystem())
			GetAISubsystem()->RegisterSensesComponent(this);
	}
}


void USensesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}


//=============================
//==========DETECTION==========
//=============================
void USensesComponent::DetectActor(AActor* Actor)
{	
	if (HasDetected(Actor))
	{
		for (auto& Detected : DetectedActors)
		{
			if (Detected.Actor == Actor)
			{
				Detected.Actor = Actor;
				Detected.DetectionState = EActorDetectionState::Detected;
				Detected.StimuliComponent = Cast<UStimuliComponent>(Actor->GetComponentByClass(UStimuliComponent::StaticClass()));
			}			
		}
	}
	/*add new reference*/
	else
	{
		FSensedActor NewDetection = FSensedActor();

		/*set actor reference*/
		NewDetection.Actor = Actor;
		/*set stimuli component reference*/
		NewDetection.StimuliComponent = Cast<UStimuliComponent>(Actor->GetComponentByClass(UStimuliComponent::StaticClass()));
		/*detection status*/
		NewDetection.DetectionState = EActorDetectionState::Detected;

		/*add to list array*/
		DetectedActors.Add(NewDetection);
	}
}

/*loop throughs all detected actors and see if this one is already in the list*/
bool USensesComponent::HasDetected(AActor* Actor)
{	
	for (auto& Detected : DetectedActors)
	{
		if (Detected.Actor == Actor)
			return true;
	}

	return false;
}

bool USensesComponent::HasDetectedAnyActors()
{
	if (DetectedActors.Num() <= 0)
		return false;

	for (auto& Detected : DetectedActors)
	{
		if (Detected.DetectionState == EActorDetectionState::Detected)
			return true;
	}

	return false;
}

void USensesComponent::LoseActor(AActor* Actor)
{
	for (auto& Detected : DetectedActors)
	{
		if (Detected.Actor == Actor)
		{
			Detected.DetectionState = EActorDetectionState::Lost;
			Detected.bSeesActor = false;
			return;
		}
	}
}

//==========================
//==========VISION==========
//==========================
void USensesComponent::OnVisionUpdate()
{
	if (GetAISubsystem() && bHasVision)
	{
		/*loop through all visual stimuli sources*/
		for (auto VisualStimuli : GetAISubsystem()->GetAllVisualStimuliComponents())
		{
			/*if we can currently see this stimuli*/
			if (CanSee(VisualStimuli->GetOwner()))
			{
				DetectActor(VisualStimuli->GetOwner());
			}
			/*if we can't see them - but had previously seen them - lose them*/
			else if(!CanSee(VisualStimuli->GetOwner()) && HasDetected(VisualStimuli->GetOwner()))
			{
				LoseActor(VisualStimuli->GetOwner());
			}
		}
	}
}

bool USensesComponent::CanSee(AActor* Actor)
{
	if (!Actor)
		return false;

	UStimuliComponent* StimuliComponent = Cast<UStimuliComponent>(Actor->GetComponentByClass(UStimuliComponent::StaticClass()));

	if (StimuliComponent && StimuliComponent->ProvidesVisualStimuli() == false)
		return false;

	if (!IsWithinSightDistance(Actor))
		return false;

	if (!IsWithinVisionCone(Actor))
		return false;


	return true;
}

bool USensesComponent::IsWithinSightDistance(AActor* Actor)
{
	if (!Actor)
		return false;
	
	if (FVector::Distance(Actor->GetActorLocation(), GetOwner()->GetActorLocation()) <= VisionDistance)
		return true;
	else
		return false;
}

bool USensesComponent::IsWithinVisionCone(AActor* Actor)
{	
	if (!Actor || !GetOwner())
		return false;

	/*stole this from PawnSensingComponent just to be clear*/
	FVector const ActorLocation = Actor->GetActorLocation();
	FVector const OurLocation = GetOwner()->GetActorLocation();
	FVector const SelfToOther = ActorLocation - OurLocation;
	FVector const SelfToOtherDir = SelfToOther.GetSafeNormal();
	FVector const MyFacingDir = GetOwner()->GetActorRotation().Vector();

	//UE_LOG(LogPath, Warning, TEXT("DotProductFacing: %f, PeripheralVisionCosine: %f"), SelfToOtherDir | MyFacingDir, FMath::Cos(FMath::DegreesToRadians(VisionConeAngle)));
	
	return ((SelfToOtherDir | MyFacingDir) >= FMath::Cos(FMath::DegreesToRadians(VisionConeAngle)));
}

