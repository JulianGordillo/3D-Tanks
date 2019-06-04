// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

class UTankBarrel;
class AProjectileBase;
class UTankTurret;

UCLASS()
class TRIDIMENTIONALBATTLE_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

	void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();

protected:

	class UTankAimingComponent* TankAimingComponent = nullptr;

private:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchVelocity = 4000.0f;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectileBase> Projectile;

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetBarrel(UTankBarrel* InBarrel);

	UFUNCTION(BlueprintCallable, Category = Setup)
	void SetTurret(UTankTurret* InTurret);

	UTankBarrel* Barrel = nullptr;

	float LastTimeFired = 0;

	UPROPERTY(EditAnywhere, Category = Firing)
	float FireRate = 3;
	
};
