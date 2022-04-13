// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/SkeletalMeshComponent.h"
#include "FirstPersonArmsComponent.generated.h"

/**
 * 
 */
UCLASS(ClassGroup=(FirstPerson), meta=(BlueprintSpawnableComponent))
class FIRSTPERSONMODULE_API UFirstPersonArmsComponent : public USkeletalMeshComponent
{
	GENERATED_BODY()
public:


	//===============================================================================================
	//===========================================FUNCTIONS===========================================
	//===============================================================================================
	UFirstPersonArmsComponent(const FObjectInitializer& ObjectInitializer);
};
