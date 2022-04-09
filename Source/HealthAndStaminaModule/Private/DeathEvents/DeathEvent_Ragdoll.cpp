// Copyright (c) 2022 Pocket Sized Animations


#include "DeathEvents/DeathEvent_Ragdoll.h"
#include "GameFramework/Character.h"
#include "Components/CapsuleComponent.h"


void UDeathEvent_Ragdoll::OnDeathEventActivated_Implementation(USimpleHealthComponent* HealthComponent, AActor* KilledActor, AActor* DeathGiver, AController* DeathInstigator)
{	
	Super::OnDeathEventActivated_Implementation(HealthComponent, KilledActor, DeathGiver, DeathInstigator);

	/*safety check*/
	if (KilledActor == nullptr)
		return;

	/*initilize*/
	USkeletalMeshComponent* Mesh = nullptr;
	UCapsuleComponent* CollisionComponent = nullptr;

	/*if we're a Character - grab the proper mesh*/
	if (ACharacter* C = Cast<ACharacter>(KilledActor))
	{
		Mesh = C->GetMesh();
		CollisionComponent = C->GetCapsuleComponent();
	}
		

	/*otherwise grab first mesh component we can find*/
	else
	{
		Mesh = Cast<USkeletalMeshComponent>(KilledActor->GetComponentByClass(USkeletalMeshComponent::StaticClass()));
		CollisionComponent = Cast<UCapsuleComponent>(KilledActor->GetComponentByClass(UCapsuleComponent::StaticClass()));
	}

	/*perform ragdoll*/
	if (Mesh != nullptr)
	{
		Mesh->SetCollisionProfileName(TEXT("Ragdoll"));
		Mesh->SetCollisionEnabled(ECollisionEnabled::PhysicsOnly);
		Mesh->SetSimulatePhysics(true);
		Mesh->SetAllBodiesSimulatePhysics(true);
		Mesh->WakeAllRigidBodies();

		if (bDisableCapsuleCollision && CollisionComponent != nullptr)
		{
			CollisionComponent->SetCollisionProfileName(TEXT("NoCollision"));
			CollisionComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);
			CollisionComponent->Deactivate();
		}
	}
}
