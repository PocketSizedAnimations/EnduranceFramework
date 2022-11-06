// Copyright (c) 2022 Pocket Sized Animations


#include "Interactives/InteractiveDoor.h"
#include "Components/InteractiveBoxComponent.h"

#include "Curves/CurveFloat.h"


/*utilities*/
#include "Components/TimelineComponent.h"

// Sets default values
AInteractiveDoor::AInteractiveDoor(const FObjectInitializer& ObjectInitializer)
{
	
	//DoorAnimationLength = 2.4f;
	TimelineComponent = ObjectInitializer.CreateDefaultSubobject<UTimelineComponent>(this, TEXT("TimelineComp"));

	
	/*animations*/
	DoorOpenAnimCurve.EditorCurveData.AddKey(0.0f, 0.0f, false);
	DoorOpenAnimCurve.EditorCurveData.AddKey(1.0f, 1.0f, false);		
	DoorOpenAnimCurve.EditorCurveData.AutoSetTangents();
	
	
	DoorCloseAnimCurve.EditorCurveData.AddKey(0.0f, 0.0f, false);
	DoorCloseAnimCurve.EditorCurveData.AddKey(1.0f, 1.0f, false);
	DoorCloseAnimCurve.EditorCurveData.AutoSetTangents();
	
	
	
	/*components*/
	SceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("SceneComp"));
	SetRootComponent(SceneComponent);

	DoorSceneComponent = ObjectInitializer.CreateDefaultSubobject<USceneComponent>(this, TEXT("DoorSceneComp"));
	if (DoorSceneComponent)
	{
		DoorSceneComponent->SetupAttachment(GetRootComponent());
		DoorSceneComponent->SetRelativeLocation(FVector(0, 65, 0));
	}

	DoorMeshComponent = ObjectInitializer.CreateDefaultSubobject<UStaticMeshComponent>(this, TEXT("DoorMeshComp"));
	if (DoorMeshComponent)
	{
		DoorMeshComponent->SetupAttachment(DoorSceneComponent);
		DoorMeshComponent->SetRelativeLocation(FVector(0, 0, 105));
	}

	InteractiveComponent = ObjectInitializer.CreateDefaultSubobject<UInteractiveBoxComponent>(this, TEXT("InteractiveComp"));
	if (InteractiveComponent)
	{
		InteractiveComponent->SetupAttachment(GetRootComponent());
		InteractiveComponent->SetRelativeLocation(FVector(0, 0, 105));
		InteractiveComponent->InitBoxExtent(FVector(15, 65, 105));

		InteractiveComponent->OnInteractionBegin.AddDynamic(this, &AInteractiveDoor::OnInteractionBegin);
	}



	/*replication*/
	bReplicates = true;
	bNetLoadOnClient = true;


	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AInteractiveDoor::BeginPlay()
{
	Super::BeginPlay();

	InitAnimationCurves();
}

void AInteractiveDoor::InitAnimationCurves()
{
	if (TimelineComponent)
	{
		/*create callbacks*/
		FOnTimelineFloat TimelineCallback;		
		TimelineCallback.BindUFunction(this, FName("OnUpdateDoorAnimation"));		
		FOnTimelineEventStatic TimelineFinishedCallback;
		TimelineFinishedCallback.BindUFunction(this, FName("OnDoorAnimationFinished"));


		/*create curve*/
		OpenAnimCurve = NewObject<UCurveFloat>();
		OpenAnimCurve->FloatCurve = *DoorOpenAnimCurve.GetRichCurve();

		/*remap the value of our initial curve to match the Door Length animation desired time*/
		//OpenAnimCurve->FloatCurve.ReadjustTimeRange(0, DoorAnimationLength,true,DoorOpenAnimCurve.GetRichCurve()->GetFirstKey().Time,DoorOpenAnimCurve.GetRichCurve()->GetLastKey().Time);

		/*update Timeline*/
		//TimelineComponent->SetFloatCurve(NewCurve, FName("Curve"));
		TimelineComponent->SetTimelineLength(OpenAnimCurve->FloatCurve.GetLastKey().Time);
		TimelineComponent->SetTimelineLengthMode(ETimelineLengthMode::TL_TimelineLength);
		TimelineComponent->SetPlaybackPosition(0.0f, false);

		TimelineComponent->AddInterpFloat(OpenAnimCurve, TimelineCallback);
		TimelineComponent->SetTimelineFinishedFunc(TimelineFinishedCallback);
	}
}

// Called every frame
void AInteractiveDoor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AInteractiveDoor::OnInteractionBegin(AActor* self, AActor* User)
{
	if (DoorState == EDoorState::Closed)
		OpenDoor();
	else if (DoorState == EDoorState::Opened)
		CloseDoor();
}

void AInteractiveDoor::OnInteractionEnd(AActor* self, AActor* User)
{

}

void AInteractiveDoor::OpenDoor()
{
	BeginOpen();
}

void AInteractiveDoor::BeginOpen()
{
	if (TimelineComponent)
	{

		DoorState = EDoorState::Opening;
		TimelineComponent->SetFloatCurve(OpenAnimCurve,FName("DoorOpen"));		
		TimelineComponent->PlayFromStart();
		//TimelineComponent->SetFloatCurve(DoorOpenAnimCurve.GetRichCurve(),FName)
	}
}

void AInteractiveDoor::OnUpdateDoorAnimation()
{
	float TimePosition = TimelineComponent->GetPlaybackPosition();
	float CurveValue = OpenAnimCurve->GetFloatValue(TimePosition);
	float NewRot = FMath::Clamp(MaxDoorOpenAngle * CurveValue,0, MaxDoorOpenAngle);
	
	if (DoorState == EDoorState::Closing)
		NewRot = MaxDoorOpenAngle - NewRot;

	DoorSceneComponent->SetRelativeRotation(FRotator(0, NewRot, 0));	
}

void AInteractiveDoor::OnDoorAnimationFinished()
{
	if (DoorState == EDoorState::Opening)
		DoorState = EDoorState::Opened;
	else
		DoorState = EDoorState::Closed;	
}


void AInteractiveDoor::EndOpen()
{

}

void AInteractiveDoor::CancelDoorOpen()
{

}

void AInteractiveDoor::CloseDoor()
{
	if(DoorState == EDoorState::Opened)
		BeginClose();
}

void AInteractiveDoor::BeginClose()
{
	if (TimelineComponent)
	{

		DoorState = EDoorState::Closing;
		TimelineComponent->SetFloatCurve(CloseAnimCurve, FName("DoorClose"));
		TimelineComponent->PlayFromStart();
	}
}

void AInteractiveDoor::EndClose()
{
}

void AInteractiveDoor::SetAnimationCurve(UCurveFloat* NewCurve)
{

}

