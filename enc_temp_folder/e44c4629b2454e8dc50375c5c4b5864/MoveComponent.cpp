// Fill out your copyright notice in the Description page of Project Settings.


#include "MoveComponent.h"

// Sets default values for this component's properties
UMoveComponent::UMoveComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UMoveComponent::EnableMovement(bool shouldMove)
{
	//Assign value and set correct tick enable state
	MoveEnable = shouldMove;
	SetComponentTickEnabled(MoveEnable);
}

void UMoveComponent::ResetMovement()
{
	//Clear distance and set to origin
	CurDistance = 0.0f;
	SetRelativeLocation(StartRelativeLocation);
}

void UMoveComponent::SetMoveDirection(int Direction)
{
	MoveDirection = Direction >= 1 ? 1 : -1;
}


// Called when the game starts
void UMoveComponent::BeginPlay()
{
	Super::BeginPlay();

	// Set Start Location
	UPROPERTY(EditAnyWhere)
	StartRelativeLocation = GetRelativeLocation();
	// Compute normalized movement
	MoveOffsetNorm = MoveOffset;
	MoveOffsetNorm.Normalize();
	MaxDistance = MoveOffset.Length();
	// Check if ticking is required
	SetComponentTickEnabled(MoveEnable);
}


// Called every frame
void UMoveComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// Set current distance
	if (MoveEnable) {
		CurDistance += DeltaTime * Speed * MoveDirection;
		if (CurDistance >= MaxDistance || CurDistance <= 0.0f) {
			// Invert direction
			MoveDirection *= -1;
			// Fire event
			OnEndpointReached.Broadcast(CurDistance >= MaxDistance);

			CurDistance = FMath::Clamp(CurDistance, 0.0f, MaxDistance);
		}
	}
	// Compute and Set Current Location
	SetRelativeLocation(StartRelativeLocation + MoveOffsetNorm * CurDistance);
}

