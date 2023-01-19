// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Subsystems/WorldSubsystem.h"
#include "AudioSubsystem.generated.h"


/* Decibal Chart
* 10bn - Normal Breathing
* 20db - Rustling leaves / mosquito
* 30db - Whispering
* 40db - Stream / Refrigerator humming
* 50db - Normal Dialogue
* 60db - Laughter
* 70db - Vacuum / hair dryer
* 75db - Dishwasher
* 80db - Garbage Disposal / city traffic
* 90db - Lawnmower
* 98db - Farm Tractor
* 100db - Train
* 103db - Jet flyover @ 100ft
* 105db - Snowmobile
* 110db - Jackhammer / power saw / symhony orchestra
* 120db - Thunderclap / boombox / .22 Rifle
* 126db - 9mm supressed
* -------damage to hearing begins --------
* 130db - Jet takeoff
* 132db - ART-15 (supressed) 
* 145db - Fireworks
* 160db - 12-gauge shotgun
* 162db - 9mm handgun
* 165db - AR-15
* 167db - .308 rifle
* 194db - perfect vacuum occurs - sound no longer can get "louder"
*/

/* A gun typically can be heard around 1-3.2km (~0.5-2miles) away
* a suppressor typicall reduces that to around 20-60meters (~65-200ft)
*
*
*/

/* Sound Loss Chart - 6db is loss per doubling of distance
* 10m - 6db
* 20m - 12db
* 40m - 18db
* 80m - 24db
* 160m - 30db
* 320m - 36db
* 640m - 42db
* 1280m - 48db
* 2560m - 54db
* 5120m - 60db
* 10240m - 66db
* 20480m - 72db
*/


/*identifying categories intended primarily to be used with AI
allowing the AI to react differently based on what sound they may of heard*/
UENUM(BlueprintType)
enum class ESoundCategory : uint8
{
	None,
	Environmental, //Generator, machinary, door opening
	EnvironmentalDisturbance, //twig snapping, leafs russeling, door being kicked, glass breaking
	Footsteps, //someone walking around
	WeaponFoley, //weapon being reloaded, or cocked
	Gunshot, //bang bang
	Explosion //grenade, C4, barrel, anything explosive
};

/** AudioSubsystem - The Audio Subsystem handles making noises and them being captured by nearby actors (with the appropriate component)
 * 
 */
UCLASS()
class AUDIBLEMODULE_API UAudioSubsystem : public UWorldSubsystem
{
	GENERATED_BODY()
public:

private:
	/*objects can register themselves with the Audio Subsystem which will be placed in this list - so that when a sound goes off it'll see who heard it and notify them*/
	UPROPERTY()
		TArray<UObject*> SoundReceivers;



public:
	UFUNCTION(BlueprintCallable, Category = "Audio Subsystem")
		virtual void MakeSound(FVector SoundLocation, ESoundCategory SoundCategory, AActor* SoundMaker = nullptr, class AController* SoundInstigator = nullptr);
	UFUNCTION(BlueprintCallable, Category = "Audio Subsystem")
		virtual void RegisterSoundReceiver(UObject* NewReceiver);

};
