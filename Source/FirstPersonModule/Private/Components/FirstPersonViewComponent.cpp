// Copyright (c) 2022 Pocket Sized Animations


#include "Components/FirstPersonViewComponent.h"
#include "Components/FirstPersonSceneComponent.h"
#include "Components/FirstPersonCameraComponent.h"
#include "Components/FirstPersonArmsComponent.h"
#include "Animations/FirstPersonArmsAnimInstance.h"

// Sets default values for this component's properties
UFirstPersonViewComponent::UFirstPersonViewComponent(const FObjectInitializer& ObjectInitializer)
{
	ArmsAnimationClass = UFirstPersonArmsAnimInstance::StaticClass();

	bAutoActivate = true;
	PrimaryComponentTick.bCanEverTick = true;
}

void UFirstPersonViewComponent::PostEditChangeProperty(struct FPropertyChangedEvent& PropertyChangedEvent)
{	
	Super::PostEditChangeProperty(PropertyChangedEvent);
}


// Called when the game starts
void UFirstPersonViewComponent::BeginPlay()
{
	Super::BeginPlay();

	/*all clients run setup*/
	InitializeFirstPersonScene();
	InitializeCameraComponent();
	InitializeArmsMesh();
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
	Arms = NewObject<UFirstPersonArmsComponent>(GetOwner(), FName("FirstPersonArms"), RF_Transient);
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
		Arms->SetAnimClass(ArmsAnimationClass);
		Arms->ResetAnimInstanceDynamics(ETeleportType::ResetPhysics);
	}
}

// Called every frame
void UFirstPersonViewComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

