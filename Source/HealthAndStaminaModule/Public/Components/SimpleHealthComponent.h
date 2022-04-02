// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);


UCLASS( ClassGroup=(Health), meta=(BlueprintSpawnableComponent) )
class HEALTHANDSTAMINAMODULE_API USimpleHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:

private:
	UPROPERTY()
		float Health;
	UPROPERTY(EditAnywhere, Category = "Health", meta = (ClampUIMin=0,ClampMin=0))
		float MaxHealth = 100.0f;


	/*events*/

	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeath;

	//=============================================================================================
	//==========================================FUNCTIONS==========================================
	//=============================================================================================

public:	
	// Sets default values for this component's properties
	USimpleHealthComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;


	//=======================================
	//=============DAMAGE EVENTS=============
	//=======================================
	UFUNCTION()
		virtual void OnReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser );
	UFUNCTION()
		virtual void OnReceivePointDamage(AActor* DamagedActor, float Damage, class AController* InstigatedBy, FVector HitLocation, class UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const class UDamageType* DamageType, AActor* DamageCauser);
	UFUNCTION()
		virtual void OnReceiveRadialDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, FVector Origin, FHitResult HitInfo, class AController* InstigatedBy, AActor* DamageCauser);
	UFUNCTION()
		virtual void InternalTakeDamage(float Damage, const class UDamageType* DamageType);


	UFUNCTION()
		virtual void BeginDeath();
	UFUNCTION()
		virtual void CompleteDeath();


	UFUNCTION()
		virtual void DisableOwnerInput();
	UFUNCTION()
		virtual void RagdollOwner(FVector Impulse);
		
};
