// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Tank.generated.h"

// Forward Declaration
class UAimingComponent;
class UTankBarrel;
class UTankTurret;
class AProjectile;

UCLASS()
class BATTLETANK_API ATank : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	ATank();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		float LaunchSpeed = 10000;

	UPROPERTY(EditDefaultsOnly, Category = "Firing")
		double ReloadTime = 3;

	UPROPERTY(EditDefaultsOnly, Category = "Setup")
		TSubclassOf<AProjectile> ProjectileBlueprint;

	double LastFireTime = 0;

	UTankBarrel* Barrel = nullptr;

protected:
	UPROPERTY(BlueprintReadOnly)
	UAimingComponent* TankAimingComponent = nullptr;

public:
	void AimAt(FVector HitLocation);

	UFUNCTION(BlueprintCallable, Category = "Action")
	void Fire();
};
