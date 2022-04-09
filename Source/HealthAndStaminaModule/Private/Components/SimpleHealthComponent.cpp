// Copyright (c) 2022 Pocket Sized Animations


#include "Components/SimpleHealthComponent.h"
#include "GameFramework/Character.h"
#include "DeathEvents/DeathEvent.h"

/*network*/
#include "Net/UnrealNetwork.h"

/*utilities*/
#include "TimerManager.h"

void USimpleHealthComponent::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME(USimpleHealthComponent, Health);
	DOREPLIFETIME(USimpleHealthComponent, Status);
}

// Sets default values for this component's properties
USimpleHealthComponent::USimpleHealthComponent()
{
	Health = MaxHealth;
	Status = EHealthState::Healthy;

	DeathCompletionLogic = EDeathCompletionLogic::Delayed;

	/*replicaiton*/
	SetIsReplicatedByDefault(true);

	/*tick*/
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void USimpleHealthComponent::BeginPlay()
{
	Super::BeginPlay();

	if (GetOwner())
	{
		GetOwner()->OnTakeAnyDamage.AddDynamic(this, &USimpleHealthComponent::OnReceiveDamage);
		GetOwner()->OnTakePointDamage.AddDynamic(this, &USimpleHealthComponent::OnReceivePointDamage);
		GetOwner()->OnTakeRadialDamage.AddDynamic(this, &USimpleHealthComponent::OnReceiveRadialDamage);
	}
}


// Called every frame
void USimpleHealthComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}



void USimpleHealthComponent::SetHealthStatus(EHealthState NewState)
{
	Status = NewState;
}

//=======================================
//=============DAMAGE EVENTS=============
//=======================================

void USimpleHealthComponent::OnReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetOwner()->HasLocalNetOwner() && GetOwner()->HasAuthority())
		GEngine->AddOnScreenDebugMessage(244, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceiveDamage()"));

	/*applies the actual damage to our health*/
	InternalTakeDamage(Damage, DamageType);

	/*!notify all clients of death!*/
	if (Health <= 0.0f)
		MulticastBeginDeath();

	float TimeSinceLastUpdate = GetWorld()->TimeSeconds - LastDamageEventTimestamp;

	if (TimeSinceLastUpdate >= DamageEventCooldown)
	{
		LastDamageEventTimestamp = GetWorld()->TimeSeconds;
		ClientOnReceiveDamage(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
	}
}

void USimpleHealthComponent::OnReceivePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	if (GetOwner()->HasLocalNetOwner() && GetOwner()->HasAuthority())
		GEngine->AddOnScreenDebugMessage(288, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceivePointDamage()"));


}

void USimpleHealthComponent::OnReceiveRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	if (GetOwner()->HasLocalNetOwner() && GetOwner()->HasAuthority())
		GEngine->AddOnScreenDebugMessage(266, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceiveRadialDamage()"));


}

void USimpleHealthComponent::InternalTakeDamage(float Damage, const UDamageType* DamageType)
{
	Health -= Damage;
	Health = FMath::Clamp(Health, 0.0f, MaxHealth);


	if (Health < MaxHealth && Status != EHealthState::Incapacitated || Status != EHealthState::Dead)
		SetHealthStatus(EHealthState::Injured);
}

void USimpleHealthComponent::ClientOnReceiveDamage_Implementation(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	if (ClientTakeAnyDamage.IsBound())
		ClientTakeAnyDamage.Broadcast(DamagedActor, Damage, DamageType, InstigatedBy, DamageCauser);
}



void USimpleHealthComponent::MulticastBeginDeath_Implementation()
{	
	SetHealthStatus(EHealthState::Dead);

	/*run through DeathEvents*/
	for (auto DeathEvent : BeginDeathEvents)
	{
		if (DeathEvent != nullptr && DeathEvent->bEnabled)
			DeathEvent->OnDeathEventActivated(this, GetOwner(), nullptr, nullptr);
	}

	/*broadcast event*/
	if (OnDeathBegin.IsBound())
		OnDeathBegin.Broadcast(GetOwner());

	/*initiate EndDeath() call (unless DeathCompletionLogic == WaitForNotification)*/
	if (DeathCompletionLogic != EDeathCompletionLogic::WaitForNotification)
	{
		if (DeathCompletionLogic == EDeathCompletionLogic::Instant)
			EndDeath();

		else if (DeathCompletionLogic == EDeathCompletionLogic::Delayed)
		{
			FTimerHandle TimeHandler;
			GetOwner()->GetWorldTimerManager().SetTimer(TimeHandler, this, &USimpleHealthComponent::EndDeath, DeathCompleteDelay, false);
		}
	}	
}

void USimpleHealthComponent::EndDeath()
{
	/*run through DeathEvents*/
	for (auto DeathEvent : EndDeathEvents)
	{
		if (DeathEvent != nullptr && DeathEvent->bEnabled)
			DeathEvent->OnDeathEventActivated(this, GetOwner(), nullptr, nullptr);
	}	
	

	if (OnDeathEnd.IsBound())
		OnDeathEnd.Broadcast(GetOwner());
}
