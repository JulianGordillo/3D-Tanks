// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"
#include "TankAimingComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	AimingComponent = GetTank()->FindComponentByClass<UTankAimingComponent>();
	if (AimingComponent)
		FoundAimingComponent(AimingComponent);
}

void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtCrosshair();
}

ATank* ATankPlayerController::GetTank() const
{
	return Cast<ATank>(GetPawn());
}

void ATankPlayerController::AimAtCrosshair()
{
	if (!GetTank()) { return; }	

	FVector HitDirection;
	if (GetCrosshairHitDirection(HitDirection))
		AimingComponent->AimAt(HitDirection);
}

/// Verdadero si pudo efectuar el cambio en el OUT parameter
bool ATankPlayerController::GetCrosshairHitDirection(FVector &out_HitDirection) const
{	
	int32 ViewportX, ViewportY; //OutParameters...
	GetViewportSize(ViewportX, ViewportY);  //...usados en esta funci?n.

	// coordenadas donde se encuentra el crosshair.
	auto ScreenLocation = FVector2D(CrosshairX * ViewportX, CrosshairY * ViewportY);

	FVector CrosshairDirection; //OUT parameter usado DeprojectCrosshairToWorld() pasa de 2D a un vector 3D en el mundo
	bool bCanDeproject = DeprojectCrosshairToWorld(ScreenLocation, CrosshairDirection);

	if (bCanDeproject) // Ya probe, en general, es siempre verdadera esta condicion aunque apuntemos al cielo. 
		return LineTraceAlongCrosshair(CrosshairDirection, out_HitDirection); //este si que puede fallar si apuntamos al cielo

	return false;
}

bool ATankPlayerController::LineTraceAlongCrosshair(FVector CrosshairDirection, FVector &out_HitDirection) const
{
	FHitResult Hit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	FVector End = Start + CrosshairDirection * LineTraceRange;
	auto QueryParams = FCollisionQueryParams(FName(), false, GetTank());
	auto ResponseParams = FCollisionResponseParams(ECR_Block);
	if (GetWorld()->LineTraceSingleByChannel(Hit,
		Start,
		End,
		ECC_Visibility,
		QueryParams,
		ResponseParams)
		)
	{
		out_HitDirection = Hit.Location;
		return true;
	}

	else
		return false;
}

//Verdadero si es posible pasar de coordenadas 2D (Crosshair) a una direccion en el mundo (3D).
bool ATankPlayerController::DeprojectCrosshairToWorld(FVector2D ScreenLocation, FVector &CrosshairDirection) const
{
	FVector WorldLocation;  ///Se descarta
	bool bCanDeproject = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, CrosshairDirection);
		return bCanDeproject;
}
