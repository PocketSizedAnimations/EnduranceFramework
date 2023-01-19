// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "SoundReceiverInterface.generated.h"


enum class ESoundCategory : uint8;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class USoundReceiverInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class AUDIBLEMODULE_API ISoundReceiverInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
		void ReceiveSoundNotification(FVector SoundLocation, ESoundCategory SoundCategory, AActor* SoundMaker = nullptr, AController* SoundInstigator = nullptr);
};
