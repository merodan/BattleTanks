// Fill out your copyright notice in the Description page of Project Settings.

#include "TankAIController.h"
#include "Engine/World.h"
#include "Tank.h"


void ATankAIController::BeginPlay()
{
	Super::BeginPlay();

	//...
}

void ATankAIController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	ATank* PlayerTank = Cast<ATank>(GetWorld()->GetFirstPlayerController()->GetPawn());
	ATank* ControlledTank = Cast<ATank>(GetPawn());
	if (ensure(PlayerTank))
	{
		// Move towards player
		MoveToActor(PlayerTank, AcceptanceRadius, true, true, true, 0, true);

		// Aim towards player
		ControlledTank->AimAt(PlayerTank->GetActorLocation());

		// Fire if ready
		ControlledTank->Fire();

		return;
	}
}

