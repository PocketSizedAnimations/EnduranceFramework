// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystems/ExtendedAISubsystem.h"
#include "SensesComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorSpotted, AActor*, Receptor, AActor*, SeenActor);

UENUM(BlueprintType)
enum class EActorDetectionState : uint8
{
	Unknown = 0,
	Detected = 1,
	Lost = 2
};

USTRUCT(BlueprintType)
struct FSensedActor
{
	GENERATED_BODY()
public:
	UPROPERTY(BlueprintReadOnly)
		AActor* Actor;	
	UPROPERTY(BlueprintReadOnly)
		class UStimuliComponent* StimuliComponent;

	UPROPERTY(BlueprintReadOnly)
		EActorDetectionState DetectionState;
	UPROPERTY(BlueprintReadOnly)
		bool bSeesActor;	
	UPROPERTY(BlueprintReadOnly)
		FVector LastKnownLocation;

};

/*component that works hand in hand with StimuliComponents to perceive things in the world*/
UCLASS( ClassGroup=(ArtificialIntelligence), meta = (BlueprintSpawnableComponent), HideCategories=(Activation, "Components|Activation", Collision))
class EXTENDEDAIMODULE_API USensesComponent : public UActorComponent
{
	friend class UBTDecorator_HasVision;

	GENERATED_BODY()
public:

protected:
	/*the actors in the world we've actually sensed*/
	UPROPERTY(BlueprintReadOnly)
		TArray<FSensedActor> DetectedActors;

protected:
	/*AI-Manager*/
	//UPROPERTY()
	//	class UAIManagerComponent* AIManager = nullptr;

	/*enable/disable vision updates*/
	UPROPERTY(EditAnywhere, Category = "Vision")
		bool bHasVision = true;
	UPROPERTY(EditAnywhere, Category = "Vision", meta=(EditCondition="bHasVision"))
		bool bShowVisionDebug = false;
	/*distance (how far away) we can see things*/
	UPROPERTY(EditAnywhere, Category = "Vision", meta = (EditCondition = "bHasVision"))
		float VisionDistance = 2400.0f;
	/*angle (width) of visual ability*/
	UPROPERTY(EditAnywhere, Category = "Vision", meta = (EditCondition = "bHasVision"))
		float VisionConeAngle = 80.0f;
	/*how long a stimuli must stay within this characters vision for it to "spot" it*/
	UPROPERTY(EditAnywhere, Category = "Vision", meta = (EditCondition = "bHasVision"))
		float VisualSpotDelay = .7f; 
	/*time between vision updates - lower is faster but less performant*/
	UPROPERTY(EditAnywhere, Category = "Vision|Advanced", meta = (EditCondition = "bHasVision", UIMin=0.05f,ClampMin=0.05f))
		float VisionUpdateInterval = 0.15f;

	FTimerHandle VisionUpdateHandler;

public:
	UPROPERTY(BlueprintAssignable)
		FOnActorSpotted OnActorSpotted;
	UPROPERTY(BlueprintAssignable)
		FOnActorSpotted OnEnemySpotted;
	


	//============================================================================================================
	//==================================================FUNCTION==================================================
	//============================================================================================================

public:	
	// Sets default values for this component's properties
	USensesComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	//=============================
	//==========DETECTION==========
	//=============================
public:
	UFUNCTION(BlueprintCallable)
		virtual void DetectActor(AActor* Actor);
	UFUNCTION(BlueprintCallable)
		virtual bool HasDetected(AActor* Actor);
	UFUNCTION(BlueprintPure)
		virtual bool HasDetectedAnyActors();
	UFUNCTION(BlueprintCallable)
		virtual void LoseActor(AActor* Actor);

	//==========================
	//==========VISION==========
	//==========================
protected:
	virtual void OnVisionUpdate();

public:
	UFUNCTION(BlueprintCallable)
		virtual bool CanSee(AActor* Actor);

protected:
	UFUNCTION(BlueprintCallable)
		bool IsWithinSightDistance(AActor* Actor);
	UFUNCTION(Blueprintcallable)
		bool IsWithinVisionCone(AActor* Actor);




	UFUNCTION()
		class UExtendedAISubsystem* GetAISubsystem() { return GetWorld()->GetSubsystem<UExtendedAISubsystem>(); }
};
