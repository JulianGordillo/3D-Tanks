// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "TankAimingComponent.generated.h"

UENUM()
enum class EFiringState : uint8
{
	Locked,
	Moving,
	Reloading
};

class UTankBarrel;
class UTankTurret;
class AProjectileBase;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class TRIDIMENTIONALBATTLE_API UTankAimingComponent : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UTankAimingComponent();

	UFUNCTION(BlueprintCallable, Category = Setup)
	void Iniciar(UTankBarrel* InBarrel, UTankTurret * InTurret);

	virtual void AimAt(FVector Location);

	UFUNCTION(BlueprintCallable, Category = Firing)
	void Fire();	
	
	bool IsBarrelMoving();

	EFiringState GetAimingState() const;

protected:

	UPROPERTY(BlueprintReadOnly)
	EFiringState AimingState = EFiringState::Reloading;

	UPROPERTY(EditAnywhere, Category = Firing)
	float LaunchVelocity = 4000.0f;

private:

	virtual void TickComponent(float DeltaTime, enum ELevelTick TickType, FActorComponentTickFunction *ThisTickFunction) override;

	UTankTurret* Turret = nullptr;	

	UTankBarrel* Barrel = nullptr;

	float LastTimeFired = 0;

	UPROPERTY(EditAnywhere, Category = Firing)
	float FireRate = 3;

	UPROPERTY(EditAnywhere, Category = Firing)
	TSubclassOf<AProjectileBase> Projectile;

	FVector AimDirection;
};
