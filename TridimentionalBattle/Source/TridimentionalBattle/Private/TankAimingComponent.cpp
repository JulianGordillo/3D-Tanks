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
	PrimaryComponentTick.bCanEverTick = true;
}


void UTankAimingComponent::Iniciar(UTankBarrel* InBarrel, UTankTurret* InTurret)
{
	Barrel = InBarrel;
	Turret = InTurret;
}

void UTankAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction * ThisTickFunction)
{
	if (GetWorld()->GetTimeSeconds() - LastTimeFired < FireRate)
	{
		AimingState = EFiringState::Reloading;
	}
	else if (IsBarrelMoving())
	{
		AimingState = EFiringState::Moving;
	}
	else
	{
		AimingState = EFiringState::Locked;
	}
}

void UTankAimingComponent::AimAt(FVector Location)
{	
	if (!Barrel || !Turret) { return; }

	FVector TossVelocity; //OUT Param
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
		TArray<AActor *>());

	if (bAimSuggestOK)
	{
		auto AimRotator = TossVelocity.GetSafeNormal().ToOrientationRotator();

		auto ActualRotator = Barrel->GetForwardVector().Rotation();
		auto DeltaRotator = AimRotator - ActualRotator;

		Barrel->Elevate(DeltaRotator.Pitch);
		if (FMath::Abs(DeltaRotator.Yaw) < 180.0f)
			Turret->RotateTurret(DeltaRotator.Yaw);
		else
			Turret->RotateTurret(-DeltaRotator.Yaw); 
	}

	AimDirection = TossVelocity.GetSafeNormal(); //get the actual normal direction of the aim

}

void UTankAimingComponent::Fire()
{
	if (!ensure(Barrel) || !ensure(Projectile)) { return; }

	if (AimingState != EFiringState::Reloading)
	{
		FVector SpawnPoint = Barrel->GetSocketLocation(FName("EndPoint"));
		FRotator SpawnRotator = Barrel->GetSocketRotation(FName("EndPoint"));
		auto SelectedProjectile = GetWorld()->SpawnActor<AProjectileBase>(Projectile, SpawnPoint, SpawnRotator);
		SelectedProjectile->Launch(LaunchVelocity);
		LastTimeFired = GetWorld()->GetTimeSeconds();
	}
}

bool UTankAimingComponent::IsBarrelMoving()
{
	return !Barrel->GetForwardVector().Equals(AimDirection, 0.01f);
}

EFiringState UTankAimingComponent::GetAimingState() const
{
	return AimingState;
}
