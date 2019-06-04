// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAimingComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Public/ProjectileBase.h"

// Sets default values for this component's properties
UTankAimingComponent::UTankAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


void UTankAimingComponent::SetBarrel(UTankBarrel * InBarrel)
{
	Barrel = InBarrel;
}

void UTankAimingComponent::SetTurret(UTankTurret * InTurret)
{
	Turret = InTurret;
}



void UTankAimingComponent::AimAt(FVector Location, float LaunchVelocity)
{
	if (!Barrel || !Turret) { return; }
	
	FVector TossVelocity;
	TArray<AActor *> IgnoreActors;
	auto TraceOption = ESuggestProjVelocityTraceOption::DoNotTrace;
	bool bAimSuggestOK = UGameplayStatics::SuggestProjectileVelocity(
		this,
		TossVelocity,
		Barrel->GetSocketLocation(FName("EndPoint")),
		Location,
		LaunchVelocity,
		false,
		0,
		0,
		TraceOption,
		ECR_Block,
		TArray<AActor *>(),
		true);

	if (bAimSuggestOK)
	{
		auto AimRotator = TossVelocity.GetSafeNormal().ToOrientationRotator();

		auto ActualRotator = Barrel->GetForwardVector().Rotation();
		auto DeltaRotator = AimRotator - ActualRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
		Turret->RotateTurret(DeltaRotator.Yaw);
	}
}
