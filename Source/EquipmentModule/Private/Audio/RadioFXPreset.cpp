// Copyright (c) 2022 Pocket Sized Animations


#include "Audio/RadioFXPreset.h"
#include "Audio/RadioFXBitCrusher.h"
#include "Audio/RadioFXBandRange.h"

URadioFXPreset::URadioFXPreset(const FObjectInitializer& ObjectInitializer)
{		
	BandRange.Preset = ObjectInitializer.CreateDefaultSubobject<URadioFXBandRange>(this, TEXT("BandRange"));
	BitCrusher.Preset = ObjectInitializer.CreateDefaultSubobject<URadioFXBitCrusher>(this, TEXT("BitCrusher"));
	Chain.Add(BandRange);
	Chain.Add(BitCrusher);
}