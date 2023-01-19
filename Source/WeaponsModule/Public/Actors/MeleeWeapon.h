// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"
#include "MeleeWeapon.generated.h"

UENUM(BlueprintType)
enum class EMeleeTraceType : uint8
{
	LineTrace,
	SphereTrace
};

/**
 * 
 */
UCLASS(abstract)
class WEAPONSMODULE_API AMeleeWeapon : public AWeapon
{
	GENERATED_BODY()
public:


	UPROPERTY(EditDefaultsOnly)
		EMeleeTraceType TraceType = EMeleeTraceType::LineTrace;
	UPROPERTY(EditDefaultsOnly)
		FName TraceStartSocketName = "TraceStartSocket";
	UPROPERTY(EditDefaultsOnly)
		FName TraceEndSocketName = "TraceEndSocket";


	//===============================================================================================================================
	//===========================================================FUNCTIONS===========================================================
	//===============================================================================================================================
public:
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer);


};
