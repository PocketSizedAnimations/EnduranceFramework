// Copyright (c) 2022 Pocket Sized Animations

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "InventoryModule/public/Interfaces/InventoryItemInterface.h"
#include "Weapon.generated.h"

UCLASS(abstract)
class WEAPONSMODULE_API AWeapon : public AActor, public IInventoryItemInterface
{
	GENERATED_BODY()
public:

	UPROPERTY(VisibleAnywhere)
		USkeletalMeshComponent* Mesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
		class UInventoryItemComponent* ItemComponent;

public:	
	// Sets default values for this actor's properties
	AWeapon(const FObjectInitializer& ObjectInitializer);

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;


public:
	UFUNCTION(BlueprintCallable, Category = "Weapons")
		virtual void BeginFire();
	UFUNCTION(BlueprintCallable, Category = "Firing")
		virtual void EndFire();



public:
	UFUNCTION()
		virtual void OnEquipBegin(AActor* Actor, UInventoryItemComponent* ItemComp, class UInventoryManagerComponent* InvManager, AActor* Equipper );
	/*UFUNCTION()
		virtual void OnEquipEnd();

	UFUNCTION()
		virtual void OnUnequipBegin();
	UFUNCTION()
		virtual void OnUnequipEnd();*/

};
