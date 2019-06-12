// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

void UTankTrack::SetAccelerator(float Acceleration)
{
	Acceleration = FMath::Clamp<float>(Acceleration, -1.0f, +1.0f);
	
	auto ForceApplied = Acceleration * MaxMovementForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}