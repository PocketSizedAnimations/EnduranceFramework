// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Curves/CurveFloat.h"
#include "Engine/DataAsset.h"
#include "ProjectileInfo.generated.h"

/**
 * 
 */
UCLASS(BlueprintType)
class WEAPONSMODULE_API UProjectileInfo : public UPrimaryDataAsset
{
	GENERATED_BODY()
public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		bool bUseVariableDamage;
	UPROPERTY(BlueprintReadWrite, EditAnywhere)
		float Damage = 25.0f;
	/*damage percentage based on dinstance traveled in meters*/
	UPROPERTY(EditAnywhere, meta = (EditCondition="bUseVariableDamage", EditConditionHides))
		FRuntimeFloatCurve DamageCurve;
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta = (Units = "m/s"))
		float Velocity = 922.0f;
	/*how many meters can this projectile go before Gravity effects it*/
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(Units="m/s"))
		float EffectiveRange = 800.0f;





	UFUNCTION()
		float GetDamage();
	
};
