// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "EngineComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Vehicles), meta = (BlueprintSpawnableComponent), HideCategories = (ComponentTick, Clothing, Physics,ClothingSimulation,SkinWeights, Navigation,VirtualTexture, ComponentReplication,Activation,Cooking,MasterPoseComponent))
class VEHICLEMODULE_API UEngineComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:	
	UPROPERTY()
		bool bEngineRunning = false;


	//===============================================================================
	//===================================FUNCTIONS===================================
	//===============================================================================


public:
	UFUNCTION()
		virtual void StartEngine();
	UFUNCTION()
		virtual void StopEngine();
	UFUNCTION(BlueprintPure, BlueprintCallable)
		virtual bool IsEngineRunning();
};
