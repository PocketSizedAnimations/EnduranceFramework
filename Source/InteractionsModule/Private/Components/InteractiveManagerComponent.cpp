// Copyright (c) 2022 Pocket Sized Animations


#include "Components/InteractiveManagerComponent.h"
#include "Camera/CameraComponent.h"
#include <InteractionsModule/Public/Interfaces/InteractiveShapeInterface.h>

#if WITH_EDITOR
#include "DrawDebugHelpers.h"
#endif

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
	CalcInteractives();
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
	{
		/*clients need to request to interact*/
		if (GetNetMode() == NM_Client)
		{
			ServerRequestInteract(Interactive);
			return true;
		}

		bInteractionSuccessful = Cast<IInteractiveShapeInterface>(Interactive)->BeginInteraction(User);
	}		

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

bool UInteractiveManagerComponent::ServerRequestInteract_Validate(UActorComponent* Interactive)
{
	return true;
}

/*ServerRequestInteract() - client requesting the server to let them begin interacting with this item*/
void UInteractiveManagerComponent::ServerRequestInteract_Implementation(UActorComponent* Interactive)
{
	Interact(Interactive);
}

void UInteractiveManagerComponent::CancelInteraction(UActorComponent* Interactive)
{
	if(!GetCurrentInteractive())
		return;

	Cast<IInteractiveShapeInterface>(GetCurrentInteractive())->CancelInteraction(GetOwner());
}




//============================================
//===========INTERACTIVES MANAGEMENT==========
//============================================

void UInteractiveManagerComponent::CalcInteractives()
{
	/*loop through all traced interactives - and see if we should add it to the list*/
	for (auto TracedInteractive : TracedInteractives)
	{
		if (Interactives.Contains(TracedInteractive) == false)
		{
			AddInteractive(TracedInteractive);			
			NotifyInteractiveOfHover(TracedInteractive);
		}
	}

	/*cleanup no-longer valid interactives*/
	for (int32 i = 0; i < Interactives.Num(); i++)
	{
		UActorComponent* Interactive = Interactives[i];
		if (TracedInteractives.Contains(Interactive) == false)
		{			
			RemoveInteractive(Interactive);			
			NotifyInteractiveOfUnhover(Interactive);
		}
	}
}

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

void UInteractiveManagerComponent::NotifyInteractiveOfHover(UActorComponent*& Interactive)
{
	if (IsInteractive(Interactive))
		Cast<IInteractiveShapeInterface>(Interactive)->OnHoverBegin(GetOwner());
}

void UInteractiveManagerComponent::NotifyInteractiveOfUnhover(UActorComponent*& Interactive)
{
	if (IsInteractive(Interactive))
		Cast<IInteractiveShapeInterface>(Interactive)->OnHoverEnd(GetOwner());
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
	/*run only for locally controlled characters to save on performance*/
	if (APawn* Pawn = Cast<APawn>(GetOwner()))
	{
		if (Pawn->IsLocallyControlled())
		{
			/*clear previous list of traced objects*/
			TracedInteractives.Empty();

			/*initialize properties*/
			TArray<FHitResult> HitResults;
			FCollisionQueryParams CollisionParams;			

			if (GetWorld()->SweepMultiByChannel(HitResults, GetTraceStart(), GetTraceEnd(), GetTraceRotation().Quaternion(), GetTraceChannel(), FCollisionShape::MakeBox(FVector(8)), CollisionParams))
			{
				/*loop through hit results*/
				for (auto HitResult : HitResults)
				{
					if (IsInteractive(Cast<UActorComponent>(HitResult.GetComponent())))
					{
						UActorComponent* HitComp = HitResult.GetComponent();						
						TracedInteractives.AddUnique(HitComp);
						
						/*debugging*/
						#if WITH_EDITOR
						if (bDebugTrace)
							DrawDebugSphere(GetWorld(), HitResult.Location, 12, 12, FColor::Cyan, false, 0.5f);
						#endif

					}
					else
					{
						/*debugging*/
						#if WITH_EDITOR
						if (bDebugTrace)
							DrawDebugSphere(GetWorld(), HitResult.Location, 12, 12, FColor::Red, false, 0.5f);
						#endif
					}
				}
			}			

			/*debugging*/
			#if WITH_EDITOR
			if (bDebugTrace)
			{
				DrawDebugLine(GetWorld(), GetTraceStart(), GetTraceEnd(), FColor::Blue, false, 0.3f, (uint8)0U, 3.0f);
			}
			#endif
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
