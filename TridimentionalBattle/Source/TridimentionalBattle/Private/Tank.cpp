// Fill out your copyright notice in the Description page of Project Settings.

#include "Public/Tank.h"
#include "Public/TankAimingComponent.h"
#include "Public/TankBarrel.h"
#include "Public/TankTurret.h"
#include "Components/InputComponent.h"
#include "Public/ProjectileBase.h"

// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	//Agregar los componentes del tanque
	TankAimingComponent = CreateDefaultSubobject<UTankAimingComponent>(FName("Tank Aiming Component"));
}


// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	PlayerInputComponent->BindAction(FName("Fire"), IE_Pressed, this, &ATank::Fire);
}

void ATank::AimAt(FVector Location)
{
	TankAimingComponent->AimAt(Location, LaunchVelocity);
}

void ATank::SetBarrel(UTankBarrel * InBarrel)
{
	TankAimingComponent->SetBarrel(InBarrel);
	Barrel = InBarrel;
}

void ATank::SetTurret(UTankTurret * InTurret)
{
	TankAimingComponent->SetTurret(InTurret);
}

void ATank::Fire()
{
	bool bIsReadyToFire = GetWorld()->GetTimeSeconds() - LastTimeFired > FireRate;

	if (Barrel && bIsReadyToFire)
	{
		FVector SpawnPoint = Barrel->GetSocketLocation(FName("EndPoint"));
		FRotator SpawnRotator = Barrel->GetSocketRotation(FName("EndPoint"));
		auto Bullet = GetWorld()->SpawnActor<AProjectileBase>(Projectile, SpawnPoint, SpawnRotator);
		Bullet->Launch(LaunchVelocity);
		LastTimeFired = GetWorld()->GetTimeSeconds();
	}

}

