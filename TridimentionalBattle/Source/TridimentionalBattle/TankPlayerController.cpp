// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
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
		GetTank()->AimAt(HitDirection);
}

bool ATankPlayerController::GetCrosshairHitDirection(FVector &out_HitDirection) const
{	
	int32 ViewportX, ViewportY;
	GetViewportSize(ViewportX, ViewportY);

	auto ScreenLocation = FVector2D(CrosshairX * ViewportX, CrosshairY * ViewportY);

	FVector CrosshairDirection; //OUT parameter usado DeprojectCrosshairToWorld()
	bool bCanDeproject = DeprojectCrosshairToWorld(ScreenLocation, CrosshairDirection);

	if (bCanDeproject)
		out_HitDirection = LineTraceAlongCrosshair(CrosshairDirection);

	return bCanDeproject;
}

FVector ATankPlayerController::LineTraceAlongCrosshair(FVector &CrosshairDirection) const
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
		return Hit.Location;
	else
		return FVector(0);

}


//Verdadero si es posible pasar de coordenadas 2D (Crosshair) a una direccion en el mundo (3D).
bool ATankPlayerController::DeprojectCrosshairToWorld(FVector2D ScreenLocation, FVector &CrosshairDirection) const
{
	FVector WorldLocation;  ///Se descarta
	bool bCanDeproject = DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, CrosshairDirection);
		return bCanDeproject;
}
