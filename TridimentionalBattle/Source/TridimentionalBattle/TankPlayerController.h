// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "TankPlayerController.generated.h"

class UTankAimingComponent;

/**
 * 
 */
UCLASS()
class TRIDIMENTIONALBATTLE_API ATankPlayerController : public APlayerController
{
	GENERATED_BODY()

public:

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;
	
protected:

	UFUNCTION(BlueprintCallable, Category = Pawn)
	class ATank* GetTank() const;

	UFUNCTION(BlueprintImplementableEvent, Category = Setup)
	void FoundAimingComponent(UTankAimingComponent* InAimingComponent);

	UPROPERTY(EditAnywhere)
	UTankAimingComponent* AimingComponent = nullptr;

private:

	UPROPERTY(EditAnywhere)
	float CrosshairX = 0.5f;

	UPROPERTY(EditAnywhere)
	float CrosshairY = 0.333f;

	UPROPERTY(EditAnywhere)
	float LineTraceRange = 10000.f;

	///Usando las funciones auxiliares debajo de AimAtCrosshair, hace que el tanque se comunique con sus componentes...
	///... y termine apuntando al crosshair.
	void AimAtCrosshair();

	///Muta el OUT parameter para obtener la posicion 3D de a donde apunta el crosshair. 
	bool GetCrosshairHitDirection(FVector &out_HitLocation) const;

	///Traza una linea desde el crosshair hacia el mundo, si choca devuelve el lugar de choque, sino devuelve (0,0,0)
	bool LineTraceAlongCrosshair(FVector CrosshairDirection, FVector &out_HitDirection) const;

	///Explicado en cpp.
	bool DeprojectCrosshairToWorld(FVector2D ScreenLocation, FVector & CrosshairDirection) const;
};
