// Fill out your copyright notice in the Description page of Project Settings.

#include "TankBarrel.h"
#include "Engine/World.h"


void UTankBarrel::Elevate(float RelativeSpeed)
{
	RelativeSpeed = FMath::Clamp<float>(RelativeSpeed, -1, +1);
	auto ElevationChange = RelativeSpeed * MaxDegreesPerSecond * GetWorld()->DeltaTimeSeconds;
	auto NewElevationRaw = RelativeRotation.Pitch + ElevationChange;
	float Elevation = FMath::Clamp<float>(NewElevationRaw, MinElevationDegrees, MaxElevationDegrees);
	SetRelativeRotation(FRotator(Elevation, 0, 0));

	// UE_LOG(LogTemp, Warning, TEXT("NewElevationRaw: %f"), Elevation);
}

