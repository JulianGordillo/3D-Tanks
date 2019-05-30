// Fill out your copyright notice in the Description page of Project Settings.

#include "MyAIController.h"
#include "../Public/Tank.h"
#include "Engine/World.h"
#include "GameFramework/PlayerController.h"

void AMyAIController::BeginPlay()
{
	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("%s is controlling %s and is aiming at %s"), *GetName(), *GetTank()->GetName(), *GetPlayerTank()->GetName())
}

void AMyAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	AimAtPlayer();
}

ATank* AMyAIController::GetTank() const
{
	return Cast<ATank>(GetPawn());
}

ATank* AMyAIController::GetPlayerTank() const
{
	///Ya que no se sabe que tipo de Pawn va a agarrar le pongo auto;
	auto PlayerTank = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (PlayerTank)
		return Cast<ATank>(PlayerTank);
	else
		return nullptr;
}

void AMyAIController::AimAtPlayer()
{
	if (GetTank())
	{
	FVector PlayerLocation = GetPlayerTank()->GetTargetLocation();
	GetTank()->AimAt(PlayerLocation);
	}
}