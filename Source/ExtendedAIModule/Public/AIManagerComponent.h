// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "AIManagerComponent.generated.h"

/*component designed to be added onto GameModes that automatically manage AI senses*/
UCLASS( ClassGroup=(ArtificialIntelligence), meta=(BlueprintSpawnableComponent) )
class EXTENDEDAIMODULE_API UAIManagerComponent : public UActorComponent
{
	GENERATED_BODY()
private:

	/*all known SensesComponents waiting stimuli*/
	UPROPERTY()
		TArray<class USensesComponent*> SensesComponents;
	/*all known StimuliComponents*/
	UPROPERTY()
		TArray<class UStimuliComponent*> StimuliComponents;

	//=========================================================================================
	//========================================FUNCTIONS========================================
	//=========================================================================================

public:	
	// Sets default values for this component's properties
	UAIManagerComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


public:
	virtual void RegisterSensesComponent(class USensesComponent* NewSensesComponent);
	virtual void RegisterStimuliComponent(class UStimuliComponent* NewStimuliComponent);


	UFUNCTION(BlueprintPure)
		TArray<class USensesComponent*> GetAllSensesComponents() {return SensesComponents;};
	UFUNCTION(BlueprintPure)
		TArray<class UStimuliComponent*> GetAllStimuluComponents() { return StimuliComponents; };
	UFUNCTION(BlueprintPure)
		TArray<class UStimuliComponent*> GetAllVisualStimuliComponents();
};
