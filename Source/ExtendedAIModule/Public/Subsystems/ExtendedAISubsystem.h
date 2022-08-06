// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "ExtendedAISubsystem.generated.h"

/**
 * 
 */
UCLASS(DisplayName = "AI Subsystem")
class EXTENDEDAIMODULE_API UExtendedAISubsystem : public UTickableWorldSubsystem
{
	GENERATED_BODY()
public:


private:
	/*************/
	/*containers*/
	/************/

	/*all pawns associated with an ExtendedAIController*/
	UPROPERTY()
		TArray<class APawn*> Pawns;
	/*all known SensesComponents waiting stimuli*/
	UPROPERTY()
		TArray<class USensesComponent*> SensesComponents;
	/*all known StimuliComponents*/
	UPROPERTY()
		TArray<class UStimuliComponent*> StimuliComponents;






	//=================================================================================================================================================
	//====================================================================FUNCTIONS====================================================================
	//=================================================================================================================================================

public:

	virtual TStatId GetStatId() const override { return TStatId(); };
	// USubsystem implementation Begin
	virtual void Initialize(FSubsystemCollectionBase& Collection) override;
	virtual void Deinitialize() override;
	// USubsystem implementation End


public:
	UFUNCTION()
		virtual void RegisterPawn(class APawn* NewPawn);
	UFUNCTION()
		virtual void RegisterSensesComponent(class USensesComponent* NewSensesComponent);
	UFUNCTION()
		virtual void RegisterStimuliComponent(class UStimuliComponent* NewStimuliComponent);


	UFUNCTION(BlueprintPure)
		TArray<class APawn*> GetAllAIPawns();
	UFUNCTION(BlueprintPure)
		TArray<class USensesComponent*> GetAllSensesComponents() { return SensesComponents; };
	UFUNCTION(BlueprintPure)
		TArray<class UStimuliComponent*> GetAllStimuluComponents() { return StimuliComponents; };
	UFUNCTION(BlueprintPure)
		TArray<class UStimuliComponent*> GetAllVisualStimuliComponents();


	

};
