// Fill out your copyright notice in the Description page of Project Settings.

#include "TankPlayerController.h"


void ATankPlayerController::BeginPlay()
{
	Super::BeginPlay();

	auto ControlledTank = GetControlledTank();
	if (!ControlledTank)
	{
		UE_LOG(LogTemp, Warning, TEXT("Failed to GetControlledTank!"));
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controlled Tank: %s"), *ControlledTank->GetName());
	}
}



ATank* ATankPlayerController::GetControlledTank() const
{
	return Cast<ATank>(GetPawn());
}
