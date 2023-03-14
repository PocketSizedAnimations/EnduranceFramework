// Copyright (c) 2022 Pocket Sized Animations


#include "Components/MovableDoorComponent.h"

/*components*/
#include "Components/InteractiveBoxComponent.h"
#include "Components/ArrowComponent.h"

/*utilities*/
#include "Components/TimelineComponent.h"

/*network*/
#include "Net/UnrealNetwork.h"


//replication setup
void UMovableDoorComponent::GetLifetimeReplicatedProps(TArray< FLifetimeProperty >& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(UMovableDoorComponent, bReplicatedDoorOpen);
}



// Sets default values for this component's properties
UMovableDoorComponent::UMovableDoorComponent(const FObjectInitializer& ObjectInitializer)
{
	/*create default animation curves*/
	//opening curve
	EditorOpenAnimCurve.EditorCurveData.AddKey(0.0f, 0.0f, false);
	EditorOpenAnimCurve.EditorCurveData.AddKey(1.0f, 1.0f, false);
	EditorOpenAnimCurve.EditorCurveData.AutoSetTangents();
	//closing curve
	EditorCloseAnimCurve.EditorCurveData.AddKey(0.0f, 0.0f, false);
	EditorCloseAnimCurve.EditorCurveData.AddKey(1.0f, 1.0f, false);
	EditorCloseAnimCurve.EditorCurveData.AutoSetTangents();

	
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComp"));
	if (SceneComponent)
	{
		SceneComponent->SetupAttachment(this);
	}
	InteractiveShapeComponent = ObjectInitializer.CreateDefaultSubobject<UInteractiveBoxComponent>(this, TEXT("InteractiveShapeComp"));
	if (InteractiveShapeComponent)
	{
		InteractiveShapeComponent->SetupAttachment(SceneComponent);
		InteractiveShapeComponent->SetBoxExtent(InteractiveExtent);
		InteractiveShapeComponent->SetRelativeLocation(FVector(0, 0, InteractiveExtent.Z));

		InteractiveShapeComponent->OnInteractionBegin.AddDynamic(this, &UMovableDoorComponent::OnInteractionBegin);
	}
	Mesh = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorMeshComp"));
	if (Mesh) 
	{
		Mesh->SetupAttachment(SceneComponent);
	}
	ArrowComponent = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("ArrowComp"));
	if (ArrowComponent)
	{
		ArrowComponent->SetupAttachment(this);
		ArrowComponent->ArrowColor = FColor::Cyan;
	}
	HingeArrowComponent = ObjectInitializer.CreateDefaultSubobject<UArrowComponent>(this, TEXT("HingeArrowComp"));
	if (HingeArrowComponent)
	{
		HingeArrowComponent->SetupAttachment(SceneComponent);
		HingeArrowComponent->ArrowColor = FColor::Magenta;
		HingeArrowComponent->SetRelativeRotation(FRotator(0, -90, 0));
	}

	TimelineComponent = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("TimelineComp"));
	
	
	Mobility = EComponentMobility::Movable;
	SetIsReplicatedByDefault(true);
	PrimaryComponentTick.bCanEverTick = true;	
}

void UMovableDoorComponent::PostEditChangeProperty(FPropertyChangedEvent& PropertyChangedEvent)
{
	Super::PostEditChangeProperty(PropertyChangedEvent);

	FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UMovableDoorComponent, StaticMesh))
	{
		if (StaticMesh && Mesh)
			Mesh->SetStaticMesh(StaticMesh);
		else if (!StaticMesh && Mesh)
			Mesh->SetStaticMesh(nullptr);

		AlignScenePosition();
	}
}


// Called when the game starts
void UMovableDoorComponent::BeginPlay()
{
	Super::BeginPlay();
	AlignScenePosition();
	InitAnimationCurves();
}


// Called every frame
void UMovableDoorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UMovableDoorComponent::OnInteractionBegin(AActor* self, AActor* User)
{
	if (GetNetMode() != NM_Client)
	{
		if (State == EDoorState::Closed)
		{
			OpenDoor();
		}
		else if (State == EDoorState::Opened)
		{
			CloseDoor();
		}
	}
}

void UMovableDoorComponent::OnInteractionEnd(AActor* self, AActor* User)
{

}

bool UMovableDoorComponent::ServerOpenDoor_Validate(AActor* User)
{
	return true;
}

void UMovableDoorComponent::ServerOpenDoor_Implementation(AActor* User)
{

}

void UMovableDoorComponent::OpenDoor()
{
	if (bLocked)
	{

	}
	else
	{
		if(GetNetMode() != NM_Client)
			bReplicatedDoorOpen = true; //notifies the client the door is opening
				
		BeginOpen();
	}

}

void UMovableDoorComponent::CloseDoor()
{
	if(GetNetMode() != NM_Client)
		bReplicatedDoorOpen = false; //notifies the client the door closing
	
	BeginClose();
}

void UMovableDoorComponent::BP_OpenDoor()
{
	if (GetNetMode() == NM_Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s::OpenDoor() called by client - this will not execute. Must be called by server"),*GetNameSafe(this))
	}
	else
		OpenDoor();
}

void UMovableDoorComponent::BP_CloseDoor()
{
	if (GetNetMode() == NM_Client)
	{
		UE_LOG(LogTemp, Warning, TEXT("%s::OpenDoor() called by client - this will not execute. Must be called by server"), *GetNameSafe(this))
	}
	else
		CloseDoor();
}

/* OnRep_DoorStateChange() - called whenever property bReplicatedDoorOpen changes which then initiates animations for client
* uses a basic bool for replication to save on overhead as well as let the client determine if it should animate
* (skipping the intermediate states of property State over network, and letting client decide that based on distance/relevancy)
*
*/
void UMovableDoorComponent::OnRep_DoorStateChange()
{
	if (bReplicatedDoorOpen) //tell client to open door
		BeginOpen();
	else
		BeginClose();
}



void UMovableDoorComponent::BeginOpen()
{
	if (TimelineComponent)
	{
		State = EDoorState::Opening;		
		TimelineComponent->SetFloatCurve(OpenAnimCurve, OpenCurveName);
		TimelineComponent->PlayFromStart();
	}
}

void UMovableDoorComponent::BeginClose()
{
	if (TimelineComponent)
	{
		State = EDoorState::Closing;
		TimelineComponent->SetFloatCurve(CloseAnimCurve, CloseCurveName);
		TimelineComponent->PlayFromStart();
	}
}


//==============================
//==========ANIMATIONS==========
//==============================

/*InitiAnimationCurves() - creates the Runtime curves from the Editor curves*/
void UMovableDoorComponent::InitAnimationCurves()
{	
	if (TimelineComponent)
	{
		/*create callbacks*/
		FOnTimelineFloat TimelineCallback;		
		TimelineCallback.BindUFunction(this, FName("OnUpdateDoorAnimation")); //called every tick the curve is processed	
		FOnTimelineEventStatic TimelineFinishedCallback;
		TimelineFinishedCallback.BindUFunction(this, FName("OnDoorAnimationFinished")); //called when curve playback reached the end


		/*create curve*/
		OpenAnimCurve = NewObject<UCurveFloat>();
		OpenAnimCurve->FloatCurve = *EditorOpenAnimCurve.GetRichCurve();		

		/*update Timeline*/
		//TimelineComponent->SetFloatCurve(NewCurve, FName("Curve"));
		TimelineComponent->SetTimelineLength(OpenAnimCurve->FloatCurve.GetLastKey().Time);
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
		TimelineComponent->SetPlaybackPosition(0.0f, false);

		TimelineComponent->AddInterpFloat(OpenAnimCurve, TimelineCallback,NAME_None,OpenCurveName);
		TimelineComponent->AddInterpFloat(CloseAnimCurve, TimelineCallback, NAME_None, CloseCurveName);
		TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedCallback);
	}	
}

void UMovableDoorComponent::OnUpdateDoorAnimation()
{	
	float TimePosition = TimelineComponent->GetPlaybackPosition();
	float CurveValue = OpenAnimCurve->GetFloatValue(TimePosition);
	
	
	if (Type == EDoorType::Swing)
	{
		float NewRot = 0.0f;
		
		if (State == EDoorState::Opening)
			NewRot = MaxOpenSwingAngle * CurveValue;
		else if (State == EDoorState::Closing)
			NewRot = MaxOpenSwingAngle - (MaxOpenSwingAngle * CurveValue);

		/*prevents us from wrecking ourselves if we get another call before the "finish" completes pushing the door to 0.0*/
		if (State == EDoorState::Opening || State == EDoorState::Closing) //only animate if we're actually opening/closing
			SceneComponent->SetRelativeRotation(FRotator(0, NewRot, 0));
	}
	else if(Type == EDoorType::Slide)
	{
		float NewPos = 0.0f;
		
		if (State == EDoorState::Opening)
			NewPos = (MaxOpenSlidePosition * CurveValue) + SceneBoundsOffset;
		else if (State == EDoorState::Closing)
			NewPos = (MaxOpenSlidePosition - (MaxOpenSlidePosition * CurveValue)) + SceneBoundsOffset;

		if (GetNetMode() == NM_Client)
		{
			UE_LOG(LogTemp, Log, TEXT("Sliding NewPos: %f"), NewPos);
		}

		/*prevents us from wrecking ourselves if we get another call before the "finish" completes pushing the door to 0.0*/
		if(State == EDoorState::Opening || State == EDoorState::Closing) //only animate if we're actually opening/closing
			SceneComponent->SetRelativeLocation(FVector(0, NewPos, 0));
	}	
}

void UMovableDoorComponent::OnDoorAnimationFinished()
{
	if (State == EDoorState::Opening)
		State = EDoorState::Opened;
	else if(State == EDoorState::Closing)
	{
		State = EDoorState::Closed;
	}
		
}

void UMovableDoorComponent::AlignScenePosition()
{
	FVector MinBounds, MaxBounds;
	Mesh->GetLocalBounds(MinBounds, MaxBounds);
	SceneBoundsOffset = MaxBounds.Y;	
	InteractionCollisionOffset = MaxBounds.Y * -1;

	SceneComponent->SetRelativeLocation(FVector(0, SceneBoundsOffset, 0));
	Mesh->SetRelativeLocation(FVector(0, (SceneBoundsOffset) * -1, 0));
	InteractiveShapeComponent->SetRelativeLocation(FVector(0, (InteractionCollisionOffset), InteractiveExtent.Z));
}

