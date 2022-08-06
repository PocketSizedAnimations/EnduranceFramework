// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "SimpleHealthComponent.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_FiveParams(FClientTakeAnyDamage, AActor*, DamagedActor, float, Damage, const class UDamageType*, DamageType, class AController*, InstigatedBy, AActor*, DamageCauser);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnDeath, AActor*, DeadActor);


/*determines whether EndDeath() logic is called instantly (or delayed), or if it waits for a notification 
from an external system (e.g: Animation Blueprint) before finishing( */
UENUM()
enum class EDeathCompletionLogic : uint8
{
	//calls EndDeath() instantly
	Instant,
	//calls EndDeath() after DeathCompleteDelay runs
	Delayed,
	//sits on standby until another system manually calls EndDeath() - great for animation based systems
	WaitForNotification
};

UENUM()
enum class EHealthState : uint8
{
	//Full Health
	Healthy,
	//Injured/Hurt/Scratched
	Injured,
	//Down - but not out
	Incapacitated,
	//Just dead.
	Dead
};


UCLASS( ClassGroup=(Health), DisplayName="Health Component", meta = (BlueprintSpawnableComponent), HideCategories = (Sockets, ComponentTick, ComponentReplication, Activation, Cooking, AssetUserData, Collision))
class HEALTHANDSTAMINAMODULE_API USimpleHealthComponent : public UActorComponent
{
	GENERATED_BODY()
public:

private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Health", meta = (ClampUIMin=0,ClampMin=0))
		float Health;
	UPROPERTY(Replicated, EditAnywhere, Category = "Health", meta = (ClampUIMin=0,ClampMin=0))
		float MaxHealth = 100.0f;
	UPROPERTY(Replicated)
		EHealthState Status;


	/*stamina*/
private:
	UPROPERTY(Replicated, EditAnywhere, Category = "Stamina", meta = (ClampUIMin = 0, ClampMin = 0))
		float Stamina;
	UPROPERTY(Replicated, EditAnywhere, Category = "Stamina", meta = (ClampUIMin = 0, ClampMin = 0))
		float MaxStamina;

	/*hunger*/
private:
	UPROPERTY(EditDefaultsOnly, Category = "Hunger")
		bool bEnableHunger;

protected:
	/*death*/
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "On Death")
		EDeathCompletionLogic DeathCompletionLogic;
	UPROPERTY(BlueprintReadOnly, EditDefaultsOnly, Category = "On Death", meta=(EditCondition="DeathCompletionLogic == EDeathCompletionLogic::Delayed" ))
		float DeathCompleteDelay = 3.0f;

	/*events to play (in order) when OnBeginDeath() is called*/
	UPROPERTY(EditDefaultsOnly, Category = "On Death", meta = (EditInline,AdvancedDisplay))
		TArray<class UDeathEvent*> BeginDeathEvents;
	/*events to play (in order0 when OnEndDeath() is called*/
	UPROPERTY(EditDefaultsOnly, Category = "On Death", meta = (EditInline,AdvancedDisplay))
		TArray<class UDeathEvent*> EndDeathEvents;

	UPROPERTY()
		float DamageEventCooldown = 0.75f;
	UPROPERTY()
		float LastDamageEventTimestamp = 0.0f;

	/*delegate events*/

	/*OWNING CLIENT ONLY - called any time this client is damaged*/
	UPROPERTY(BlueprintAssignable)
		FClientTakeAnyDamage ClientTakeAnyDamage;

	/*called whenever an actor first gets notification it just died*/
	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeathBegin;
	/*called after OnDeathBegin completes (defined by DeathCompletionLogic enumerator)*/
	UPROPERTY(BlueprintAssignable)
		FOnDeath OnDeathEnd;


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

	//==========================
	//==========HEALTH==========
	//==========================
	UFUNCTION()
		virtual void SetHealthStatus(EHealthState NewState);
	
	
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

	UFUNCTION(Client, Reliable)
		virtual void ClientOnReceiveDamage(AActor* DamagedActor, float Damage, const class UDamageType* DamageType, class AController* InstigatedBy, AActor* DamageCauser);


	UFUNCTION(NetMulticast, Reliable)
		virtual void MulticastBeginDeath();
	UFUNCTION()
		virtual void EndDeath();




};
