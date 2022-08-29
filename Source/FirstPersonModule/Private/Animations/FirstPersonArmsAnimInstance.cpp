// Copyright (c) 2022 Pocket Sized Animations


#include "Animations/FirstPersonArmsAnimInstance.h"
#include "GameFramework/PawnMovementComponent.h"





void UFirstPersonArmsAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
}

void UFirstPersonArmsAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);

	OnUpdateMovementStates();
	OnUpdateItemStates();
}


//=====================================================
//=======================ITEMS=======================
//=====================================================

void UFirstPersonArmsAnimInstance::OnUpdateItemStates()
{	
	//fill in your item updates here
	UpdateCurrentlyEquippedItem();
	UpdateItemEquipState();
}

void UFirstPersonArmsAnimInstance::UpdateCurrentlyEquippedItem()
{

}

void UFirstPersonArmsAnimInstance::UpdateItemEquipState()
{

}

void UFirstPersonArmsAnimInstance::ClearItemState()
{
	CurrentItemState = EAnimState_ItemState::NoCurrentItem;
}

bool UFirstPersonArmsAnimInstance::IsEquippingItem()
{
	if (CurrentItemState == EAnimState_ItemState::Equipping)
		return true;

	return false;
}

bool UFirstPersonArmsAnimInstance::HasItemEquipped()
{
	if (CurrentItemState == EAnimState_ItemState::Equipped)
		return true;

	return false;
}

bool UFirstPersonArmsAnimInstance::IsUnequippingItem()
{
	if (CurrentItemState == EAnimState_ItemState::Unequipping)
		return true;

	return false;
}

void UFirstPersonArmsAnimInstance::OnUpdateMovementStates()
{
	if (!TryGetPawnOwner())
		return;

	UpdateMovementState();
}

void UFirstPersonArmsAnimInstance::UpdateMovementState()
{
	if (TryGetPawnOwner() && TryGetPawnOwner()->GetMovementComponent())
	{
		MovementVelocity = TryGetPawnOwner()->GetMovementComponent()->Velocity.Size();
		if (MovementVelocity > 0)
		{
			bMoving = true;

			if (MovementVelocity > SprintSpeed)
				MovementState = EAnimState_MovementState::Sprinting;
			if (MovementVelocity > RunSpeed)
				MovementState = EAnimState_MovementState::Running;
			else if (MovementVelocity > WalkSpeed)
				MovementState = EAnimState_MovementState::Walking;
		}
			
		else
		{
			bMoving = false;
			MovementState = EAnimState_MovementState::NotMoving;
		}
	}
}

bool UFirstPersonArmsAnimInstance::IsMoving()
{
	return bMoving;
}

bool UFirstPersonArmsAnimInstance::IsRunning()
{
	if (MovementState == EAnimState_MovementState::Running)
		return true;

	return false;
}

bool UFirstPersonArmsAnimInstance::IsSprinting()
{
	if (MovementState == EAnimState_MovementState::Sprinting)
		return true;

	return false;
}

