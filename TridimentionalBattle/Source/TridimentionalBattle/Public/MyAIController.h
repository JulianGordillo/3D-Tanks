// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class UTankAimingComponent;

UCLASS()
class TRIDIMENTIONALBATTLE_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

protected:

	UPROPERTY(EditAnywhere)
	UTankAimingComponent* AimingComponent = nullptr;

private:

	UPROPERTY(EditAnywhere, Category = AI)
	float AcceptableRadius = 1500.0f;

	class ATank* AITank = nullptr;
};
