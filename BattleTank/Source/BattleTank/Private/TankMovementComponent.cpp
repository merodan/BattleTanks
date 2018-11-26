// Fill out your copyright notice in the Description page of Project Settings.

#include "TankMovementComponent.h"
#include "TankTrack.h"


void UTankMovementComponent::Initialise(UTankTrack* SetLeftTrack, UTankTrack* SetRightTrack)
{
	LeftTrack = SetLeftTrack;
	RightTrack = SetRightTrack;
}


void UTankMovementComponent::IntendMoveForward(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(Throw);

	UE_LOG(LogTemp, Warning, TEXT("IntendMoveForward: %f"), Throw)
}


void UTankMovementComponent::IntendTurnRight(float Throw)
{
	if (!LeftTrack || !RightTrack) { return; }
	LeftTrack->SetThrottle(Throw);
	RightTrack->SetThrottle(-Throw);

	UE_LOG(LogTemp, Warning, TEXT("IntendTurnRight: %f"), Throw)
}