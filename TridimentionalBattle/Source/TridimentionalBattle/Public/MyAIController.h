// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "MyAIController.generated.h"

class ATank;

UCLASS()
class TRIDIMENTIONALBATTLE_API AMyAIController : public AAIController
{
	GENERATED_BODY()

public:

	void BeginPlay() override;

	void Tick(float DeltaTime) override;

};
