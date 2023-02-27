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



protected:

	/*flag for indicating this weapon is actively tracing for damage*/
	UPROPERTY()
		bool bAttacking;
	UPROPERTY(VisibleAnywhere)
		EMeleeTraceType TraceType = EMeleeTraceType::LineTrace;
	UPROPERTY(EditDefaultsOnly)
		TEnumAsByte<ECollisionChannel> TraceChannel;
	UPROPERTY(EditDefaultsOnly)
		bool bDebugTrace;

	UPROPERTY(EditDefaultsOnly)
		FName TraceStartSocketName = "TraceStartSocket";
	UPROPERTY(EditDefaultsOnly)
		FName TraceEndSocketName = "TraceEndSocket";



	//===============================================================================================================================
	//===========================================================FUNCTIONS===========================================================
	//===============================================================================================================================
public:
	AMeleeWeapon(const FObjectInitializer& ObjectInitializer);
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintCallable, Category = "Attacking")
		virtual void BeginLightAttack();
	UFUNCTION(BlueprintCallable, Category = "Attacking")
		virtual void BeginHeavyAttack();
	UFUNCTION(BlueprintCallable, Category = "Attacking")
		virtual void BeginThrustingAttack();

public:
	virtual void BeginFire() override;
	virtual void EndFire() override;

protected:
	UFUNCTION()
		virtual void OnAttackBegin();
	UFUNCTION()
		virtual void OnAttackEnd();

private:
	/*performs the actual weapon trace*/
	UFUNCTION()
		virtual void PerformWeaponTrace();
	/*event when the weapon trace hits something*/
	UFUNCTION()
		virtual void OnTraceHit(FHitResult HitResults);
};
