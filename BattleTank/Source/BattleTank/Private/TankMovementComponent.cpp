// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"
#include "Engine/World.h"


void UTankMovementComponent::Initialise(UTankTrack* SetLeftTrack, UTankTrack* SetRightTrack)
{
	LeftTrack = SetLeftTrack;
	RightTrack = SetRightTrack;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (ensure(!LeftTrack || !RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (ensure(!LeftTrack || !RightTrack)) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);
}

void UTankMovementComponent::RequestDirectMove(const FVector& MoveVelocity, bool bForceMaxSpeed)
{
	// No need to call Super, because the functionality is being replaced

	// Normal Vector of the Pathfinding 
	FVector TankForward = GetOwner()->GetActorForwardVector().GetSafeNormal();

	// Direction the AI wants to move
	FVector AIForwardIntention = MoveVelocity.GetSafeNormal();

	float ForwardThrow = FVector::DotProduct(TankForward, AIForwardIntention);
	IntendMoveForward(ForwardThrow);

	float RightThrow = FVector::CrossProduct(TankForward, AIForwardIntention).Z;
	IntendTurnRight(RightThrow);

	// UE_LOG(LogTemp, Warning, TEXT("Forward: %f, Right: %f"), ForwardThrow, RightThrow);
}
