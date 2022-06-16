// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Actors/Weapon.h"

#include "Firearm.generated.h"


/**
 * 
 */
UCLASS(abstract)
class WEAPONSMODULE_API AFirearm : public AWeapon
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, Category = "Projectiles")
		FName ProjectileSocketName = FName("MuzzleSocket");
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Projectiles")
		class UProjectileSpawnerComponent* ProjectileSpawnerComponent;

	//=====================================================================================
	//=====================================FUNCTIONS=======================================
	//=====================================================================================
public:
	AFirearm(const FObjectInitializer& ObjectInitializer);



	virtual void BeginFire() override;
	virtual void EndFire() override;

	
};
