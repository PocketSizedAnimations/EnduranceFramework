// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/GameInstanceSubsystem.h"
#include "ModSubsystem.generated.h"

/**
 * 
 */
UCLASS()
class MODMANAGEMENTMODULE_API UModSubsystem : public UGameInstanceSubsystem
{
	GENERATED_BODY()
public:


	UPROPERTY(BlueprintReadOnly, Category = "Maps, Mods, & Mutators")
		TArray<class AMapInfo*> AvailableMaps;
	UPROPERTY(BlueprintReadOnly, Category = "Maps, Mods, & Mutators")
		TArray<class AMod*> AvailableMods;
	UPROPERTY(BlueprintReadOnly, Category = "Maps, Mods, & Mutators")
		TArray<class AMutator*> AvailableMutators;
	




	//=========================================================================================================================
	//========================================================FUNCTIONS========================================================
	//=========================================================================================================================

	/*add a map to the list of custom maps available to be loaded*/
	UFUNCTION(BlueprintCallable, Category = "Maps, Mods, & Mutators")
		virtual void AddMap(class AMapInfo* NewMap);


	UFUNCTION(BlueprintPure, Category = "Maps, Mods, & Mutators")
		TArray<class AMapInfo*> GetMapsOfCategory(FName Category = NAME_None);
};
