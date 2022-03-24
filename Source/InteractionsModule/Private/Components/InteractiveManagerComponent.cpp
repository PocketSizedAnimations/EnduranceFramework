// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InteractiveManagerComponent.h"
#include "Camera/CameraComponent.h"
#include <InteractionsModule/Public/Interfaces/InteractiveShapeInterface.h>

UInteractiveManagerComponent::UInteractiveManagerComponent()
{	
	TraceLength = 100.0f;
	
	/*tick setup*/
	PrimaryComponentTick.bCanEverTick = true;
	PrimaryComponentTick.TickInterval = 0.15f;
}


void UInteractiveManagerComponent::BeginPlay()
{
	Super::BeginPlay();	
}



void UInteractiveManagerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	/*perform trace*/
	TraceForInteractives();
	UpdateActiveInteractiveStatus();	
}


//================================================
//==================INTERACTIONS==================
//================================================
bool UInteractiveManagerComponent::Interact(UActorComponent* Interactive)
{
	/*safety check*/
	if (!Interactive)
		return false;

	/*initialize*/
	bool bInteractionSuccessful = false;
	AActor* User = GetOwner();
	AActor* InteractiveActor = Interactive->GetOwner();
	
	/*attempt interaction*/
	if (IsInteractive(Interactive))
		bInteractionSuccessful = Cast<IInteractiveShapeInterface>(Interactive)->BeginInteraction(User);

	/*broadcast results*/
	if (bInteractionSuccessful)	{

		ActiveInteraction = Interactive;			
		return true;
	}
	else
	{
		/*broadcast failure*/
		if (OnInteractionDenied.IsBound())
			OnInteractionDenied.Broadcast(InteractiveActor, User);

		return false;
	}	
}

void UInteractiveManagerComponent::CancelInteraction(UActorComponent* Interactive)
{
	if(!GetCurrentInteractive())
		return;

	Cast<IInteractiveShapeInterface>(GetCurrentInteractive())->EndInteraction(GetOwner(), true);
}




//============================================
//===========INTERACTIVES MANAGEMENT==========
//============================================

bool UInteractiveManagerComponent::IsInteractive(UActorComponent* Interactive)
{
	/*check for valid interfacing implementation*/
	if (!Cast<IInteractiveShapeInterface>(Interactive))
		return false;

	/*check component itself*/
	if (!Cast<IInteractiveShapeInterface>(Interactive)->IsInteractionEnabled())
		return false;

	/*return true if all is well*/
	return true;
}

void UInteractiveManagerComponent::AddInteractive(UActorComponent*& Interactive)
{
	Interactives.AddUnique(Interactive);
}

void UInteractiveManagerComponent::RemoveInteractive(UActorComponent*& Interactive)
{
	Interactives.Remove(Interactive);
}

void UInteractiveManagerComponent::ClearInteractives()
{
	Interactives.Empty();
}

void UInteractiveManagerComponent::ClearActiveInteraction()
{
	ActiveInteraction = nullptr;
}

void UInteractiveManagerComponent::UpdateActiveInteractiveStatus()
{
	if (IsActiveInteractionComplete())
		ActiveInteraction = nullptr;
}

UActorComponent* UInteractiveManagerComponent::GetCurrentInteractive()
{
	if (Interactives.Num() <= 0)
		return nullptr;

	return Interactives[0];
}

//===============================
//============TRACING============
//===============================
void UInteractiveManagerComponent::TraceForInteractives()
{	
	TArray<FHitResult> HitResults;
	FCollisionQueryParams CollisionParams;

	ClearInteractives();

	if(GetWorld()->SweepMultiByChannel(HitResults, GetTraceStart(), GetTraceEnd(), GetTraceRotation().Quaternion(), GetTraceChannel(), FCollisionShape::MakeBox(FVector(8)), CollisionParams))
	{
		/*loop through hit results*/
		for (auto HitResult : HitResults)
		{
			if (IsInteractive(Cast<UActorComponent>(HitResult.GetComponent())))
			{
				UActorComponent* HitComp = HitResult.GetComponent();
				AddInteractive(HitComp);				
			}
		}
	}
}

FVector UInteractiveManagerComponent::GetTraceStart()
{
	/*default location starts at Actor location*/
	FVector StartLocation = GetOwner()->GetActorLocation();
	FRotator Rotation;

	/*look for controller if our owner is a Pawn type*/
	if (TraceType == EInteractiveTraceType::Controller && Cast<APawn>(GetOwner()))
	{
		APawn* Pawn = Cast<APawn>(GetOwner());
		if (Pawn && Pawn->GetController())
			Pawn->GetController()->GetPlayerViewPoint(StartLocation, Rotation);
	}
	/*look for owner actor's camera*/
	else if (TraceType == EInteractiveTraceType::Camera && GetOwner() && GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))
	{

	}

	return StartLocation;
}

FVector UInteractiveManagerComponent::GetTraceEnd()
{
	FVector EndLocation = FVector(0);
	FRotator ViewRotation = FRotator(0);
	

	/*look for controller if our owner is a Pawn type*/
	if (TraceType == EInteractiveTraceType::Controller && Cast<APawn>(GetOwner()))
	{
		APawn* Pawn = Cast<APawn>(GetOwner());
		if (Pawn && Pawn->GetController())
		{
			Pawn->GetController()->GetPlayerViewPoint(EndLocation, ViewRotation);
		}
	}
	/*look for owner actor's camera*/
	else if (TraceType == EInteractiveTraceType::Camera && GetOwner() && GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))
	{

	}
	/*fallback to actor center otherwise*/
	else
	{

	}

	return EndLocation + (ViewRotation.Vector() * TraceLength);
}

FRotator UInteractiveManagerComponent::GetTraceRotation()
{
	FVector Location;
	FRotator TraceRotation = GetOwner()->GetActorRotation();

	/*look for controller if our owner is a Pawn type*/
	if (TraceType == EInteractiveTraceType::Controller && Cast<APawn>(GetOwner()))
	{
		APawn* Pawn = Cast<APawn>(GetOwner());
		if (Pawn && Pawn->GetController())
		{
			Pawn->GetController()->GetPlayerViewPoint(Location, TraceRotation);
		}
	}
	/*look for owner actor's camera*/
	else if (TraceType == EInteractiveTraceType::Camera && GetOwner() && GetOwner()->GetComponentByClass(UCameraComponent::StaticClass()))
	{

	}

	return TraceRotation;
}

ECollisionChannel UInteractiveManagerComponent::GetTraceChannel()
{
	return UEngineTypes::ConvertToCollisionChannel(TraceChannel);	
}

bool UInteractiveManagerComponent::IsActiveInteractionComplete()
{
	/*safety check*/
	if (ActiveInteraction == nullptr)
		return true;

	/*initialize & check*/
	IInteractiveShapeInterface* Interactive = Cast<IInteractiveShapeInterface>(ActiveInteraction);
	if (Interactive == nullptr)
		return false;

	if (Interactive->GetRemainingInteractionTime() <= 0)
		return true;
	else
		return false;	
}
