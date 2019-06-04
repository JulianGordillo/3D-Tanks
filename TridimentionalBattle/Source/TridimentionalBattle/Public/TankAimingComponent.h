// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

class UTankBarrel;
class UTankTurret;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIDIMENTIONALBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	virtual void AimAt(FVector Location, float LaunchVelocity);

	void SetBarrel(UTankBarrel * InBarrel);	

	void SetTurret(UTankTurret * InTurret);

protected:

	UTankBarrel* Barrel = nullptr;

	UTankTurret* Turret = nullptr;	
};
