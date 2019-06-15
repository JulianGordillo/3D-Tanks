// Fill out your copyright notice in the Description page of Project Settings.

#include "TankTrack.h"

UTankTrack::UTankTrack()
{
	PrimaryComponentTick.bCanEverTick = false;
}

void UTankTrack::BeginPlay()
{
	Super::BeginPlay();
	OnComponentHit.AddDynamic(this, &UTankTrack::OnHit);
}

void UTankTrack::AddCorrectionForce()
{
	//hay que saber cuanto deslizamiento hay que corregir en esta frame
	auto DeltaTime = GetWorld()->GetDeltaSeconds();
	auto Deslizamiento = FVector::DotProduct(GetComponentVelocity(), GetRightVector());
	auto Correccion = -(Deslizamiento / DeltaTime)*GetRightVector();

	auto TankRoot = Cast<UStaticMeshComponent>(GetOwner()->GetRootComponent());
	auto ForceApplied = (TankRoot->GetMass() * Correccion) / 2; //2 tracks

	TankRoot->AddForce(ForceApplied);
}

void UTankTrack::SetAccelerator(float Acceleration)
{
	CurrentAcceleration = FMath::Clamp<float>(CurrentAcceleration + Acceleration, -1, +1);
}

void UTankTrack::DriveTrack()
{
	auto ForceApplied = CurrentAcceleration * MaxMovementForce * GetForwardVector();
	auto ForceLocation = GetComponentLocation();

	auto TankRoot = Cast<UPrimitiveComponent>(GetOwner()->GetRootComponent());
	TankRoot->AddForceAtLocation(ForceApplied, ForceLocation);
}

void UTankTrack::OnHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	DriveTrack();
	AddCorrectionForce();
	CurrentAcceleration = 0.0f;
}