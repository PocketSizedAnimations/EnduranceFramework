// Copyright (c) 2022 Pocket Sized Animations


#include "Components/FirstPersonViewComponent.h"
#include "Components/FirstPersonSceneComponent.h"
#include "Components/FirstPersonCameraComponent.h"
#include "Components/FirstPersonArmsComponent.h"
#include "Animations/FirstPersonArmsAnimInstance.h"

/*ui*/
#include "Blueprint/UserWidget.h"

// Sets default values for this component's properties
UFirstPersonViewComponent::UFirstPersonViewComponent(const FObjectInitializer& ObjectInitializer)
{
	//ArmsAnimationClass = UFirstPersonArmsAnimInstance::StaticClass();
	bWantsInitializeComponent = true;

	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFirstPersonViewComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{	
	/*FName PropertyName = (PropertyChangedEvent.Property != NULL) ? PropertyChangedEvent.Property->GetFName() : NAME_None;

	if (PropertyName == GET_MEMBER_NAME_CHECKED(UFirstPersonViewComponent, ViewHeight))
	{
		SyncPawnEyeHeight();
	}*/

	Super::PostEditChangeProperty(PropertyChangedEvent);
}

void UFirstPersonViewComponent::PostInitProperties()
{	
	Super::PostInitProperties();
	SyncPawnEyeHeight();
}

void UFirstPersonViewComponent::InitializeComponent()
{
	/*all clients run setup*/
	InitializeFirstPersonScene();
	InitializeCameraComponent();
	InitializeArmsMesh();
	SyncPawnEyeHeight();
	

	Super::InitializeComponent();

}


// Called when the game starts
void UFirstPersonViewComponent::BeginPlay()
{
	Super::BeginPlay();
}

void UFirstPersonViewComponent::InitializeFirstPersonScene()
{
	if (Scene != nullptr || GetOwner() == nullptr)
		return;

	/*create Root Scene*/
	Scene = NewObject<UFirstPersonSceneComponent>(GetOwner(), FName("FirstPersonScene"), RF_Transient);	
	if (Scene)
	{
		/*initialize*/
		Scene->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Scene->RegisterComponent();
		Scene->Activate();

		/*position*/
		Scene->SetRelativeLocation(FVector(ViewForwardOffset, 0, ViewHeight));
	}
}

void UFirstPersonViewComponent::InitializeCameraComponent()
{
	/*safety checks*/
	if (Camera != nullptr || Scene == nullptr || GetOwner() == nullptr)
		return;

	/*create camera*/
	Camera = NewObject<UFirstPersonCameraComponent>(GetOwner(), FName("FirstPersonCamera"), RF_Transient);
	if (Camera)
	{
		/*initialize*/
		Camera->AttachToComponent(Scene,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Camera->RegisterComponent();
		Camera->Activate();		
	}
}

void UFirstPersonViewComponent::InitializeArmsMesh()
{
	if (Arms != nullptr || ArmsMesh == nullptr)
		return;

	/*create arms*/
	Arms = NewObject<UFirstPersonArmsComponent>(GetOwner(), ArmsMeshName, RF_Transient);
	if (Arms)
	{
		/*initialize*/
		Arms->AttachToComponent(Scene,FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		Arms->RegisterComponent();
		Arms->Activate();
		
		/*setup placement*/
		Arms->SetRelativeLocation(ArmsOffset);

		/*initialize visuals*/
		Arms->SetSkeletalMesh(ArmsMesh);
		Arms->SetAnimClass(AnimationBlueprint);
		Arms->ResetAnimInstanceDynamics(ETeleportType::ResetPhysics);

		/*ensure we hide this from anyone but the owning player*/
		Arms->SetOnlyOwnerSee(true);
	}
}

void UFirstPersonViewComponent::SyncPawnEyeHeight()
{
	if (APawn* P = Cast<APawn>(GetOwner()))
	{
		P->BaseEyeHeight = ViewHeight;		
	}
}

// Called every frame
void UFirstPersonViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFirstPersonViewComponent::InitializePlayerHUD(APlayerController* PlayerController)
{
	if (!HUDClass || !GetOwner())
		return;

	/*local-pawn check - no need to add widget otherwise*/
	APawn* Pawn = Cast<APawn>(GetOwner());
	if (!Pawn->IsLocallyControlled())
		return;
	
	if (PlayerController)
	{
		PlayerHUD = CreateWidget<UUserWidget>(PlayerController, HUDClass,"PlayerHUDWidget");
		PlayerHUD->AddToViewport();
		
		if (bAutoShowHUD)
		{
			PlayerHUD->AddToViewport(999);
		}
	}
}

