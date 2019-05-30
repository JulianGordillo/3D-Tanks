// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TRIDIMENTIONALBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;	
	void Tick(float DeltaTime) override;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f;
	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.333f;
	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000.f;

	class ATank* GetTank() const;
	void AimAtCrosshair();
	bool GetCrosshairHitDirection(FVector &out_HitLocation) const;
	FVector LineTraceAlongCrosshair(FVector &CrosshairDirection) const;
	bool DeprojectCrosshairToWorld(FVector2D ScreenLocation, FVector & CrosshairDirection) const;
};
