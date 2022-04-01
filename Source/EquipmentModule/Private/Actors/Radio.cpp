// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/Radio.h"
#include "Sound/SoundEffectSource.h"
#include "Audio/RadioFXPreset.h"
#include "Components/AudioComponent.h"
#include "Components/BillboardComponent.h"

ARadio::ARadio(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	Range = 2.5f;
	
	Frequencies.Init(0, 7);	
	Frequencies[0] = 87.8f;
	Frequencies[1] = 89.5f;
	Frequencies[2] = 91.3f;
	Frequencies[3] = 94.6f;
	Frequencies[4] = 96.6f;
	Frequencies[5] = 99.7f;
	Frequencies[6] = 102.5f;

	RadioFX = ObjectInitializer.CreateDefaultSubobject<URadioFXPreset>(this, TEXT("RadioFXChain"));
	AudioComponent = ObjectInitializer.CreateDefaultSubobject<UAudioComponent>(this, TEXT("AudioComponent"));
	if (AudioComponent)
	{
		AudioComponent->SetSourceEffectChain(RadioFX);		
		AudioComponent->VolumeMultiplier = Volume;
	}
	

	FRichCurve* QualityRangeCurve = RangeQuality.GetRichCurve();
	QualityRangeCurve->Reset();
	QualityRangeCurve->AddKey(0.0f, 1.0f);
	QualityRangeCurve->AddKey(Range - 0.25f, 0.65f);
	QualityRangeCurve->AddKey(Range, 0.25f);
	QualityRangeCurve->AddKey(Range + 0.5f, 0.0f);

#if WITH_EDITORONLY_DATA
	UBillboardComponent* SpriteComp = Cast<UBillboardComponent>(GetComponentByClass(UBillboardComponent::StaticClass()));
	if (SpriteComp)
	{		
		SpriteComp->SetVisibility(false, true);
		SpriteComp->ScreenSize = 0.0f;
	}
#endif
}


void ARadio::BeginPlay()
{	
	Super::BeginPlay();

}



void ARadio::IncreaseVolume()
{

}

void ARadio::DecreaseVolume()
{

}


void ARadio::ReceiveTransmission(USoundBase* IncomingSound, FVector TransmissionSourceLocation)
{
	if (!AudioComponent || !IncomingSound)
		return;

	AudioComponent->SetSound(IncomingSound);
	AudioComponent->Play();
}

float  ARadio::GetCurrentFrequency()
{
	if (Frequencies.Num() >= CurrentFrequencyIndex)
	{
		return Frequencies[CurrentFrequencyIndex];
	}
	
	return -1;
}

FString ARadio::GetCurrentFrequencyAsText()
{
	return FString::SanitizeFloat(GetCurrentFrequency());
}



float ARadio::GetTransmissionQuality(FVector TransmissionSourceLocation)
{	
	float Distance = FVector::Distance(GetActorLocation(), TransmissionSourceLocation);
	Distance = Distance / 100000; //convert to km


	if (!RangeQuality.GetRichCurve())
		return -1.0f;
	
	return RangeQuality.GetRichCurve()->Eval(Distance);
}