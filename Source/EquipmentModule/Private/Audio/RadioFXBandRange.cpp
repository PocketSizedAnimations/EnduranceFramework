// Copyright (c) 2022 Pocket Sized Animations


#include "Audio/RadioFXBandRange.h"

URadioFXBandRange::URadioFXBandRange()
{
	Settings.FilterCircuit = ESourceEffectFilterCircuit::Ladder;
	Settings.FilterType = ESourceEffectFilterType::BandPass;
	Settings.CutoffFrequency = 3200.0f;
	Settings.FilterQ = 0.5f;	
}
