// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"

void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto DeltaElevation = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevation = RelativeRotation.Pitch + DeltaElevation;

	NewElevation = FMath::Clamp<float>(NewElevation, MinElevation, MaxElevation);
	SetRelativeRotation(FRotator(NewElevation, 0.0f, 0.0f));
}
