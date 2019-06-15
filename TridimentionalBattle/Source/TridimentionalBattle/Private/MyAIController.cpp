// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "../Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"
#include "TankAimingComponent.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	AITank = Cast<ATank>(GetPawn());
	AimingComponent = AITank->FindComponentByClass<UTankAimingComponent>();
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());

	if (ensure(AITank && PlayerTank))
	{
		//Siempre que se mueva hacia el jugador y que pare a 30 metros
		MoveToActor(PlayerTank, AcceptableRadius);

		//Que siempre apunte y dispare al jugador
		AimingComponent->AimAt(PlayerTank->GetTargetLocation());
		if(AimingComponent->GetAimingState() == EFiringState::Locked)
			AimingComponent->Fire();
	}
}


