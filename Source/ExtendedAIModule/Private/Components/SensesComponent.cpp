// Copyright (c) 2022 Pocket Sized Animations


#include "Components/SensesComponent.h"
#include "GameFramework/Actor.h"
#include "GameFramework/GameModeBase.h"
#include "Components/StimuliComponent.h"
#include "AudibleModule/Public/Subsystems/AudioSubsystem.h"

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
		/*begin vision updates*/
		if (bHasVision)
			GetOwner()->GetWorldTimerManager().SetTimer(VisionUpdateHandler, this, &USensesComponent::OnVisionUpdate, VisionUpdateInterval, true);
	
		/*register senses to AI Subsystem*/
		if (UExtendedAISubsystem* AISubsystem = GetAISubsystem())
			AISubsystem->RegisterSensesComponent(this);

		/*register hearing to AudioSubsystem*/
		if (bHasHearing) 
		{
			if (UAudioSubsystem* AudioSubsytem = GetAudioSubsystem())
				AudioSubsytem->RegisterSoundReceiver(this);
		}
	}
}


void USensesComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

void USensesComponent::SetAlertState(EAlertState NewAlertState)
{
	/*no changes if same alert*/
	if (GetAlertState() == NewAlertState)
		return;


	PreviousAlertState = AlertState;
	AlertState = NewAlertState;
}

EAlertState USensesComponent::GetAlertState()
{
	return AlertState;
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

bool USensesComponent::HasDetectedAnyActors(TSubclassOf<AActor> ClassFilter)
{
	if (DetectedActors.Num() <= 0)
		return false;

	for (auto& Detected : DetectedActors)
	{
		if (Detected.DetectionState == EActorDetectionState::Detected && IsValid(Detected.Actor) && Detected.Actor->IsA(ClassFilter))
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

TArray<AActor*> USensesComponent::GetDetectedActors()
{
	TArray<AActor*> ActorList;

	for (auto Detected : DetectedActors)
	{
		if (Detected.DetectionState == EActorDetectionState::Detected)
			ActorList.Add(Detected.Actor);
	}

	return ActorList;
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


//===========================
//==========HEARING==========
//===========================

/*Produced by ISoundReceiverInterface - must register SensesComponent to AudioSubsystem to be eligable for sound reception!*/
void USensesComponent::ReceiveSoundNotification_Implementation(FVector SoundLocation, ESoundCategory SoundCategory, AActor* SoundMaker, AController* SoundInstigator)
{
	if(!bHasHearing)
		return;

	LastHeardSound = FSoundEvent(SoundLocation, SoundCategory, GetWorld()->TimeSeconds);

	/*produce notification*/
	if (OnSoundHeard.IsBound())
		OnSoundHeard.Broadcast(SoundLocation, SoundCategory, SoundMaker, SoundInstigator);
}

bool USensesComponent::HeardNoise()
{
	if(!bHasHearing || LastHeardSound.Timestamp < 0)
		return false;

	if (LastHeardSound.Timestamp <= GetWorld()->TimeSeconds)
		return true;

	return false;

}

UAudioSubsystem* USensesComponent::GetAudioSubsystem()
{
	return GetWorld()->GetSubsystem<UAudioSubsystem>();
}

