// Copyright (c) 2022 Pocket Sized Animations


#include "Components/FirstPersonItemComponent.h"
#include "Components/FirstPersonViewComponent.h"
#include "Components/FirstPersonArmsComponent.h"

// Sets default values for this component's properties
UFirstPersonItemComponent::UFirstPersonItemComponent()
{
	
	bWantsInitializeComponent = true;	
	PrimaryComponentTick.bCanEverTick = true;
}


void UFirstPersonItemComponent::InitializeComponent()
{
	Super::InitializeComponent();

	InitializeFirstPersonMesh();
}

// Called when the game starts
void UFirstPersonItemComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFirstPersonItemComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UFirstPersonItemComponent::InitializeFirstPersonMesh()
{
	if (SkeletalMeshComp != nullptr || FirstPersonMesh == nullptr)
		return;

	/*create arms*/
	SkeletalMeshComp = NewObject<USkeletalMeshComponent>(GetOwner(), MeshName, RF_Transient);
	if (SkeletalMeshComp)
	{
		/*initialize*/
		SkeletalMeshComp->AttachToComponent(GetOwner()->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
		SkeletalMeshComp->RegisterComponent();
		SkeletalMeshComp->Activate();

		/*setup placement*/
		//SkeletalMeshComp->SetRelativeLocation(ArmsOffset);

		/*initialize visuals*/
		SkeletalMeshComp->SetSkeletalMesh(FirstPersonMesh);
		SkeletalMeshComp->SetAnimClass(AnimationBlueprint);
		SkeletalMeshComp->ResetAnimInstanceDynamics(ETeleportType::ResetPhysics);

		/*set it so only the owning player sees this version*/
		SkeletalMeshComp->SetOnlyOwnerSee(true);
	}
}

void UFirstPersonItemComponent::AttachFirstPersonMesh()
{	
	if (APawn* Pawn = GetOwningPawn())
	{
		if (UFirstPersonViewComponent* FPV = Cast<UFirstPersonViewComponent>(Pawn->GetComponentByClass(UFirstPersonViewComponent::StaticClass())))
		{
			if (FPV->GetArmsMeshComponent())
			{
				SkeletalMeshComp->AttachToComponent(FPV->GetArmsMeshComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, GetAttachmentSocketName());
			}
		}
	}
}

FName UFirstPersonItemComponent::GetAttachmentSocketName()
{
	//@TODO : update this to be more dynamic
	return FName("RightHandSocket");
}

APawn* UFirstPersonItemComponent::GetOwningPawn()
{
	APawn* _pawn = nullptr;
	AActor* _owner = GetOwner();

	while (_pawn == nullptr)
	{
		if (_owner == nullptr)
			return nullptr;

		_pawn = Cast<APawn>(_owner);
		if (_pawn)
			return _pawn;

		else
			_owner = _owner->GetOwner();
	}
	
	return nullptr;
}

