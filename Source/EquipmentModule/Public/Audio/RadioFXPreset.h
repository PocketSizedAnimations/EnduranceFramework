// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Sound/SoundEffectSource.h"
#include "RadioFXPreset.generated.h"

/**
 * 
 */
UCLASS()
class EQUIPMENTMODULE_API URadioFXPreset : public USoundEffectSourcePresetChain
{
	GENERATED_BODY()
public:

	FSourceEffectChainEntry BandRange = FSourceEffectChainEntry();
	FSourceEffectChainEntry BitCrusher = FSourceEffectChainEntry();
	
	URadioFXPreset(const FObjectInitializer& ObjectInitializer);
};
