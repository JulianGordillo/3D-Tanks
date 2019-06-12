// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "TankTrack.generated.h"

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRIDIMENTIONALBATTLE_API UTankTrack : public UStaticMeshComponent
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	void SetAccelerator(float Acceleration);

private:
	UPROPERTY(EditAnywhere)
	float MaxMovementForce = 400000.0f; // 40Ton tank mass and 10m/s2 (1G) acceleration => Force = mass * acc

};
