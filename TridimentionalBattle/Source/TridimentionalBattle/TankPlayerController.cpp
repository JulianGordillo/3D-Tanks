// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Public/Tank.h"
#include "Engine/World.h"
#include "Camera/CameraComponent.h"

void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();
	if(GetTank()) 
	UE_LOG(LogTemp, Warning, TEXT("%s is controlling %s"), *GetName() , *GetTank()->GetName())
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
	FVector CrosshairDirection;

	if (DeprojectCrosshairToWorld(ScreenLocation, CrosshairDirection))
	{
		///Crea la Linea entre el crosshair y el mundo con una longitud establecida.
		out_HitDirection = LineTraceAlongCrosshair(CrosshairDirection);
		return true;
	}

	else
		return false;

}

FVector ATankPlayerController::LineTraceAlongCrosshair(FVector &CrosshairDirection) const
{
	FHitResult Hit;
	FVector Start = PlayerCameraManager->GetCameraLocation();
	auto QueryParams = FCollisionQueryParams(FName(), false, GetTank());
	auto ResponseParams = FCollisionResponseParams(ECR_Block);
	if (GetWorld()->LineTraceSingleByChannel(Hit,
		Start,
		Start + CrosshairDirection * LineTraceRange,
		ECC_Visibility,
		QueryParams,
		ResponseParams)
		)
		return Hit.Location;
	else
		return FVector(0.0f);

}


//Verdadero si es posible pasar de coordenadas 2D (Crosshair) a una direccion en el mundo (3D).
bool ATankPlayerController::DeprojectCrosshairToWorld(FVector2D ScreenLocation, FVector &CrosshairDirection) const
{
	FVector WorldLocation;  ///Se descarta
	return DeprojectScreenPositionToWorld(ScreenLocation.X, ScreenLocation.Y, WorldLocation, CrosshairDirection);
}
