// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"
#include "Tank.h"
#include "Engine/World.h"
#include "AimingComponent.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	UAimingComponent* AimingComponent = GetControlledTank()->FindComponentByClass<UAimingComponent>();
	if (AimingComponent)
	{
		// Broadcast method to BP, no implementation in C++ needed.
		FoundAimingComponent(AimingComponent);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("PlayerController can't find AimingComponent at BeginPlay()."));
	}
}


void ATankPlayerController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	// UE_LOG(LogTemp, Warning, TEXT("PlayerController Tick working!"));
	AimTowardsCrossHair();

}


ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}


void ATankPlayerController::AimTowardsCrossHair()
{
	if (ensure(!GetControlledTank())) { return; }
	
	FVector HitLocation; // OUT Parameter
	if (GetSightRayHitLocation(HitLocation))
	{
		// UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *HitLocation.ToString());

		// TODO make the tank aim
		GetControlledTank()->AimAt(HitLocation);
	}
}


bool ATankPlayerController::GetSightRayHitLocation(FVector& OutHitLocation) const
{
	// Get Screensize
	int32 ViewportSizeX, ViewportSizeY;
	GetViewportSize(ViewportSizeX, ViewportSizeY);

	// Calculate CrossHair location
	auto CrossHairLocation = FVector2D(ViewportSizeX * CrossHairXLocation, ViewportSizeY * CrossHairYLocation);

	// De-project the crosshair position to a world direction and get looking angle
	FVector LookDirection;
	if (GetLookDirection(CrossHairLocation, LookDirection))
	{
		// UE_LOG(LogTemp, Warning, TEXT("Look Direction: %s"), *LookDirection.ToString());

		GetLookVectorHitLocation(LookDirection, OutHitLocation);
	}

	return true;
}


bool ATankPlayerController::GetLookDirection(FVector2D CrossHairLocation, FVector& LookDirection) const
{
	FVector CameraWorldLocation;
	return DeprojectScreenPositionToWorld(
		CrossHairLocation.X, 
		CrossHairLocation.Y, 
		CameraWorldLocation, 
		OUT LookDirection
	);
}


bool ATankPlayerController::GetLookVectorHitLocation(FVector LookDirection, FVector& OutHitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(
		OUT HitResult, 
		StartLocation, 
		EndLocation, 
		ECollisionChannel::ECC_Visibility)
	)
	{
		OutHitLocation = HitResult.Location;
		return true;
	}
	else
	{
		OutHitLocation = FVector(0);
		return false;
	}
}
