// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/NavMovementComponent.h"
#include "TankMovementComponent.generated.h"

class UTankTrack;

/**
 * 
 */
UCLASS(ClassGroup = (Custom), meta = (BlueprintSpawnableComponent))
class TRIDIMENTIONALBATTLE_API UTankMovementComponent : public UNavMovementComponent
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendMovementForward(float Movement);
	
	UFUNCTION(BlueprintCallable, Category = Input)
	void IntendTurnRight(float Movement);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Iniciar(UTankTrack * InRightTrack, UTankTrack * InLeftTrack);

private:

	virtual void RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed) override;

	float MaxForce = 100.0f;
	
	UTankTrack* RightTrack = nullptr;
	
	UTankTrack* LeftTrack = nullptr;
};
