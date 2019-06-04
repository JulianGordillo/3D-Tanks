// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTurret.h"

void UTankTurret::RotateTurret(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto DeltaRotation = RelativeSpeed * MaxRotationPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewRotation = RelativeRotation.Yaw + DeltaRotation;

	SetRelativeRotation(FRotator(0.0f, NewRotation, 0.0f));
}
