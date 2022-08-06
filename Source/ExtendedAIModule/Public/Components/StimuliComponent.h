// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Subsystems/ExtendedAISubsystem.h"
#include "StimuliComponent.generated.h"

/*component that automatically produces reactions to SensesComponent to reprepsent vision and hearing events*/
UCLASS( ClassGroup=(ArtificialIntelligence), meta=(BlueprintSpawnableComponent) )
class EXTENDEDAIMODULE_API UStimuliComponent : public UActorComponent
{
	GENERATED_BODY()
public:

	/*visibility*/
	UPROPERTY(EditAnywhere)
		bool bVisualStimuli = true;
	
	
	/*noise-making*/
	UPROPERTY(EditAnywhere)
		bool bAudioStimuli = true;

	//=============================================================================
	//==================================FUNCTIONS==================================
	//=============================================================================

public:	
	// Sets default values for this component's properties
	UStimuliComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	
	virtual bool ProvidesVisualStimuli();





	UFUNCTION()
		class UExtendedAISubsystem* GetAISubsystem() { return GetWorld()->GetSubsystem<UExtendedAISubsystem>(); }
};
