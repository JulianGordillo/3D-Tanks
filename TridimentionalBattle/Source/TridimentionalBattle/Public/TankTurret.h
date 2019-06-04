// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTurret.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRIDIMENTIONALBATTLE_API UTankTurret : public UStaticMeshComponent
{
	GENERATED_BODY()

private:

	UPROPERTY(EditAnywhere)
	float MaxRotationPerSecond = 5.0f;

public:
	void RotateTurret(float RelativeSpeed);
};
