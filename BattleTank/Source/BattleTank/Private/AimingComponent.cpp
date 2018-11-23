// Fill out your copyright notice in the Description page of Project Settings.

#include "AimingComponent.h"
#include "TankBarrel.h" // Barrel used in cpp, so #include is needed instead of forward declaration
#include "TankTurret.h"


// Sets default values for this component's properties
UAimingComponent::UAimingComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UAimingComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UAimingComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UAimingComponent::AimAt(FVector HitLocation, float LaunchSpeed)
{
	/*auto PlayerTankName = GetOwner()->GetName();
	auto BarrelLocation = Barrel->GetComponentLocation();
	UE_LOG(LogTemp, Warning, TEXT("%s aiming at %s from %s"), *PlayerTankName, *HitLocation.ToString(), *BarrelLocation.ToString());*/

	if (!Barrel) { return; }
	FVector LaunchVelocity(0);
	FVector StartLocation = Barrel->GetSocketLocation(FName("Projectile"));
	
	bool bHaveAimSolution = UGameplayStatics::SuggestProjectileVelocity(
		this,
		LaunchVelocity,
		StartLocation,
		HitLocation,
		LaunchSpeed,
		false,
		0,
		0,
		ESuggestProjVelocityTraceOption::DoNotTrace
	);

	if (bHaveAimSolution)
	{
		// Get Direction
		auto LaunchDirection = LaunchVelocity.GetSafeNormal();
		MoveBarrelTowards(LaunchDirection);

		float Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: Aim solution found!"), Time);
	}
	else
	{
		float Time = GetWorld()->GetTimeSeconds();
		// UE_LOG(LogTemp, Warning, TEXT("%f: No aim solution found."), Time);
	}
}


void UAimingComponent::SetBarrelReference(UTankBarrel* SetBarrel)
{
	Barrel = SetBarrel;
}

void UAimingComponent::SetTurretReference(UTankTurret* SetTurret)
{
	Turret = SetTurret;
}


void UAimingComponent::MoveBarrelTowards(FVector LaunchDirection)
{
	auto BarrelRotator = Barrel->GetForwardVector().Rotation();
	auto AimAsRotator = LaunchDirection.Rotation();
	auto DeltaRotator = AimAsRotator - BarrelRotator;

	// Elevation
	Barrel->Elevate(DeltaRotator.Pitch);

	// Rotation
	Turret->Rotate(DeltaRotator.Yaw);
}
