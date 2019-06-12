// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"

// Sets default values
ATank::ATank()
{
	PrimaryActorTick.bCanEverTick = false;
}

void ATank::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
		AimingComponentFound(AimingComponent);
}



