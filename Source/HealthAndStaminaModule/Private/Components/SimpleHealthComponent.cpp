// Copyright (c) 2022 Pocket Sized Animations


#include "Components/SimpleHealthComponent.h"
#include "GameFramework/Character.h"

// Sets default values for this component's properties
USimpleHealthComponent::USimpleHealthComponent()
{
	Health = MaxHealth;

	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
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

void USimpleHealthComponent::OnReceiveDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceiveDamage()"));
	
	/*applies the actual damage to our health*/
	InternalTakeDamage(Damage, DamageType);

	if (Health <= 0.0f)
		BeginDeath();
}

void USimpleHealthComponent::OnReceivePointDamage(AActor* DamagedActor, float Damage, AController* InstigatedBy, FVector HitLocation, UPrimitiveComponent* FHitComponent, FName BoneName, FVector ShotFromDirection, const UDamageType* DamageType, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceivePointDamage()"));


}

void USimpleHealthComponent::OnReceiveRadialDamage(AActor* DamagedActor, float Damage, const UDamageType* DamageType, FVector Origin, FHitResult HitInfo, AController* InstigatedBy, AActor* DamageCauser)
{
	GEngine->AddOnScreenDebugMessage(-1, 10.0f, FColor::Red, TEXT("USimpleHealthComponent::OnReceiveRadialDamage()"));


}

void USimpleHealthComponent::InternalTakeDamage(float Damage, const UDamageType* DamageType)
{
	Health -= Damage;

	Health = FMath::Clamp(Health, 0.0f, MaxHealth);
}



void USimpleHealthComponent::BeginDeath()
{	


	if (OnDeath.IsBound())
		OnDeath.Broadcast(GetOwner());
}

void USimpleHealthComponent::CompleteDeath()
{

}

void USimpleHealthComponent::DisableOwnerInput()
{
	if (!GetOwner())
		return;

	if (ACharacter* P = Cast<ACharacter>(GetOwner()))
	{
		APlayerController* PC = Cast<APlayerController>(P->GetController());
		P->DisableInput(PC);
	}	
}

void USimpleHealthComponent::RagdollOwner(FVector Impulse)
{

}

