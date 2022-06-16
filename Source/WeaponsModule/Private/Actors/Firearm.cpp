// Copyright (c) 2022 Pocket Sized Animations


#include "Actors/Firearm.h"

/*projetiles*/
#include "Components/ProjectileSpawnerComponent.h"

AFirearm::AFirearm(const FObjectInitializer& ObjectInitializer)
	:Super(ObjectInitializer)
{
	ProjectileSpawnerComponent = ObjectInitializer.CreateDefaultSubobject<UProjectileSpawnerComponent>(this, TEXT("Projectile Spawner"));
	
	if (ProjectileSpawnerComponent)
	{
		ProjectileSpawnerComponent->SetupAttachment(Mesh);
	}
}

void AFirearm::BeginFire()
{
	Super::BeginFire();

	if (ProjectileSpawnerComponent)
	{
		ProjectileSpawnerComponent->BeginFire();
	}
}

void AFirearm::EndFire()
{
	Super::EndFire();

	if (ProjectileSpawnerComponent)
	{
		ProjectileSpawnerComponent->EndFire();
	}
}
