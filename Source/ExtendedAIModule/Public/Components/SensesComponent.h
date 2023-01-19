// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystems/ExtendedAISubsystem.h"
#include "AudibleModule/Public/Interfaces/SoundReceiverInterface.h"
#include "SensesComponent.generated.h"

enum class ESoundCategory : uint8;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnActorSpotted, AActor*, Receptor, AActor*, SeenActor);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_FourParams(FOnSoundHeard, FVector, SoundLocation, ESoundCategory, SoundCategory, AActor*, SoundMaker, AController*, SoundInstigator);

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

USTRUCT(BlueprintType)
struct FSoundEvent
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadOnly)
		FVector Location;
	UPROPERTY(BlueprintReadOnly)
		ESoundCategory Category;
	UPROPERTY(BlueprintReadOnly)
		float Timestamp;

	FSoundEvent()
	{
		Location = FVector(-1, -2, -3);		
		Timestamp = -1.0f;
	}

	FSoundEvent(FVector location, ESoundCategory category, float timeStamp)
	{
		Location = location;
		Category = category;
		Timestamp = timeStamp;
	}
};

UENUM(BlueprintType)
enum class EAlertState : uint8
{
	Disabled,
	Low,
	Medium,
	High
};

/*component that works hand in hand with StimuliComponents to perceive things in the world*/
UCLASS( ClassGroup=(ArtificialIntelligence), meta = (BlueprintSpawnableComponent), HideCategories=(Activation, "Components|Activation", Collision))
class EXTENDEDAIMODULE_API USensesComponent : public UActorComponent, public ISoundReceiverInterface
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

	UPROPERTY(EditAnywhere, Category = "Alertness")
		EAlertState AlertState = EAlertState::Medium;
	UPROPERTY()
		EAlertState PreviousAlertState = EAlertState::Disabled;

	/************VISION************/
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

	/***************HEARING**********/
	/*turn on to enable hearing*/
	UPROPERTY(EditAnywhere, Category = "Hearing")
		bool bHasHearing = true;
	/*time between now and LastHeardSound event that is considered "recently heard"*/
	UPROPERTY(VisibleAnywhere, Category = "Hearing")
		float HeardSoundRecentlyThreshold = 2.0f;
	UPROPERTY()
		FSoundEvent LastHeardSound;


public:
	UPROPERTY(BlueprintAssignable)
		FOnActorSpotted OnActorSpotted;
	UPROPERTY(BlueprintAssignable)
		FOnActorSpotted OnEnemySpotted;
	UPROPERTY(BlueprintAssignable)
		FOnSoundHeard OnSoundHeard;
	
	

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
	//==========ALERTNESS==========
	//=============================
public:
	UFUNCTION(BlueprintCallable)
		virtual void SetAlertState(EAlertState NewAlertState);
	UFUNCTION(BlueprintPure, Category = "Alertness")
		EAlertState GetAlertState();
	
	//=============================
	//==========DETECTION==========
	//=============================
public:
	UFUNCTION(BlueprintCallable)
		virtual void DetectActor(AActor* Actor);
	UFUNCTION(BlueprintCallable)
		virtual bool HasDetected(AActor* Actor);
	UFUNCTION(BlueprintPure)
		virtual bool HasDetectedAnyActors(TSubclassOf<AActor> ClassFilter);
	UFUNCTION(BlueprintCallable)
		virtual void LoseActor(AActor* Actor);

	/*returns a list of actors that this senses component currently has detected*/
	UFUNCTION()
		TArray<AActor*> GetDetectedActors();

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

	//===========================
	//==========HEARING==========
	//===========================
	protected: 
		/*sound notification from AudioSubsystem interface ISoundReceiverInterface*/
		void ReceiveSoundNotification_Implementation(FVector SoundLocation, ESoundCategory SoundCategory, AActor* SoundMaker = nullptr, AController* SoundInstigator = nullptr) override;
	public:
		UFUNCTION(BlueprintPure, Category = "Senses|Hearing")
			bool HeardNoise();



	UFUNCTION()
		class UExtendedAISubsystem* GetAISubsystem() { return GetWorld()->GetSubsystem<UExtendedAISubsystem>(); }
	UFUNCTION()
		class UAudioSubsystem* GetAudioSubsystem();

};
