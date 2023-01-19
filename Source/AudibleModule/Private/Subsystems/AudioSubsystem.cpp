// Copyright (c) 2022 Pocket Sized Animations


#include "Subsystems/AudioSubsystem.h"
#include "Interfaces/SoundReceiverInterface.h"

void UAudioSubsystem::MakeSound(FVector SoundLocation, ESoundCategory SoundCategory, AActor* SoundMaker, AController* SoundInstigator)
{
	for (UObject* Receiver : SoundReceivers)
	{
		UE_LOG(LogTemp, Log, TEXT("MakeSound::%s"), *Receiver->GetName());

		Cast<ISoundReceiverInterface>(Receiver)->Execute_ReceiveSoundNotification(Receiver, SoundLocation, SoundCategory, SoundMaker, SoundInstigator);
	}
}

void UAudioSubsystem::RegisterSoundReceiver(UObject* NewReceiver)
{
	/*safety/type check (needs to implement interface)*/
	if (!NewReceiver || !NewReceiver->Implements<USoundReceiverInterface>())
		return;

	if (SoundReceivers.Contains(NewReceiver))
		return;

	SoundReceivers.Add(NewReceiver);
}
