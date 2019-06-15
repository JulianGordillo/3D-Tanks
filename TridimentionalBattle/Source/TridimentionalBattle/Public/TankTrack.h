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

	UTankTrack();

	UFUNCTION(BlueprintCallable, Category = Movement)
	void SetAccelerator(float Acceleration);

	void DriveTrack();

private:

	float CurrentAcceleration = 0;

	UFUNCTION()
	void OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit );

	virtual void BeginPlay() override;

	void AddCorrectionForce();

	UPROPERTY(EditAnywhere)
	float MaxMovementForce = 400000.0f; // 40Ton tank mass and 10m/s2 (1G) acceleration => Force = mass * acc

};
