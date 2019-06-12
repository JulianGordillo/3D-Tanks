// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "Public/TankTrack.h"

void UTankMovementComponent::Iniciar(UTankTrack* InRightTrack, UTankTrack* InLeftTrack)
{
	if (!InRightTrack || !InLeftTrack) { return; }

	RightTrack = InRightTrack;
	LeftTrack = InLeftTrack;
}

void UTankMovementComponent::RequestDirectMove(const FVector & MoveVelocity, bool bForceMaxSpeed)
{
	auto IntendedMove = MoveVelocity.GetSafeNormal();
	auto TankForwardVector = GetOwner()->GetActorForwardVector().GetSafeNormal();

	//cantidad de movimento (float) que va a recibir la funcion de movimiento (las de abajo).
	auto ForwardMovement = FVector().DotProduct(IntendedMove, TankForwardVector);
	auto RightMovement = FVector().CrossProduct(TankForwardVector, IntendedMove).Z;
	IntendMovementForward(ForwardMovement);
	IntendTurnRight(RightMovement);
}

void UTankMovementComponent::IntendMovementForward(float Movement)
{
	RightTrack->SetAccelerator(Movement);
	LeftTrack->SetAccelerator(Movement);
}

void UTankMovementComponent::IntendTurnRight(float Movement)
{
	RightTrack->SetAccelerator(-Movement);
	LeftTrack->SetAccelerator(Movement);
}