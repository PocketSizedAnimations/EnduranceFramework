// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/Equipment.h"
#include "Radio.generated.h"

USTRUCT()
struct FRadioQuality
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
		float CutoffFrequency = 3200.0f;
	UPROPERTY(EditAnywhere)
		float FilterQ = 0.5f;
	UPROPERTY(EditAnywhere)
		float SampleRate = 4200.0f;
	UPROPERTY(EditAnywhere)
		float BitDepth = 8.0f;
};

/**
 * 
 */
UCLASS()
class EQUIPMENTMODULE_API ARadio : public AEquipment
{
	GENERATED_BODY()
public:
	
	UPROPERTY(EditAnywhere, Category = "Radio")
		float Volume = 1.0f;
	/*range - in km*/
	UPROPERTY(EditDefaultsOnly, Category = "Radio", meta = (DisplayName = "Range (km)"))
		float Range = 2.5f;
	UPROPERTY(EditDefaultsOnly, Category = "Radio")
		float Interference = 0;	

	UPROPERTY(EditDefaultsOnly, meta = (DisplayName = "Default Frequency Index"))
		uint8 CurrentFrequencyIndex;
	UPROPERTY(EditDefaultsOnly, Category = "Radio")
		TArray<float> Frequencies;
	
	/*will automatically applie the chain of effects onto incoming transmissions for this radio*/
	UPROPERTY(EditDefaultsOnly, Category = "Sound FX", Instanced, meta = (DisplayName = "Radio FX"))
		class USoundEffectSourcePresetChain* RadioFX;
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Audio")
		UAudioComponent* AudioComponent;


	/*audio distortion*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "Audio Distortion")
		FRuntimeFloatCurve RangeQuality;



	//=====================================================================================
	//======================================FUNCTIONS======================================
	//=====================================================================================
public:
	ARadio(const FObjectInitializer& ObjectInitializer);

	virtual void BeginPlay() override;


	UFUNCTION(BlueprintCallable, Category = "Radio")
		virtual void IncreaseVolume();
	UFUNCTION(BlueprintCallable, Category = "Radio")
		virtual void DecreaseVolume();

	UFUNCTION(BlueprintCallable, Category = "Transmissions")
		virtual void ReceiveTransmission(class USoundBase* IncomingTransmission, FVector TransmissionSourceLocation);

	UFUNCTION(BlueprintPure, BlueprintCallable)
		float GetCurrentFrequency();
	UFUNCTION(BlueprintPure, BlueprintCallable)
		FString GetCurrentFrequencyAsText();


	UFUNCTION(BlueprintPure, Category = "Tranmissions")
		float GetTransmissionQuality(FVector TransmissionSourceLocation);

	
};
