// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "../Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	auto PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	auto AITank = Cast<ATank>(GetPawn());

	if (AITank && PlayerTank)
	{
		AITank->AimAt(PlayerTank->GetTargetLocation());
		AITank->Fire();
	}
}


