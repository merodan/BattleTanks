// Fill out your copyright notice in the Description page of Project Settings.

#include "Tank.h"
#include "AimingComponent.h"
#include "TankMovementComponent.h"
#include "Engine/World.h"
#include "TankBarrel.h" // Barrel used in cpp, so #include is needed instead of forward declaration
#include "TankTurret.h"
#include "Projectile.h"


// Sets default values
ATank::ATank()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// No need to protect pointers in the constructor

	TankAimingComponent = CreateDefaultSubobject<UAimingComponent>(FName("Aiming Component"));
}

// Called when the game starts or when spawned
void ATank::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATank::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void ATank::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

// Needed to make it callable in Blueprint
void ATank::SetBarrelReference(UTankBarrel* SetBarrel)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->SetBarrelReference(SetBarrel);
	Barrel = SetBarrel;
}

// Needed to make it callable in Blueprint
void ATank::SetTurretReference(UTankTurret* SetTurret)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->SetTurretReference(SetTurret);
}


void ATank::AimAt(FVector HitLocation)
{
	if (!TankAimingComponent) { return; }
	TankAimingComponent->AimAt(HitLocation, LaunchSpeed);
}


void ATank::Fire()
{
	bool isReloaded = (GetWorld()->GetTimeSeconds() - LastFireTime) > ReloadTime;

	if (Barrel && isReloaded)
	{
		// Launches a projectile at the socket location of the barrel
		auto Projectile = GetWorld()->SpawnActor<AProjectile>(
			ProjectileBlueprint,
			Barrel->GetSocketLocation(FName("Projectile")),
			Barrel->GetSocketRotation(FName("Projectile"))
			);
		if (!Projectile) { return; }
		Projectile->LaunchProjectile(LaunchSpeed);
		// Reset to current game time
		LastFireTime = GetWorld()->GetTimeSeconds();
	}
}