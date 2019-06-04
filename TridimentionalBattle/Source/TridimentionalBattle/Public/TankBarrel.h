// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankBarrel.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRIDIMENTIONALBATTLE_API UTankBarrel : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:

	void Elevate(float Elevate);

private:
	
	UPROPERTY(EditAnywhere)
	float MaxDegreesPerSecond = 1.0f;

	UPROPERTY(EditAnywhere)
	float MaxElevation = 40.0f;
	
	UPROPERTY(EditAnywhere)
	float MinElevation = 0.0f;

};
