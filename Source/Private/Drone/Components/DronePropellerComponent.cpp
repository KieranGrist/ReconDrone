// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/Components/DronePropellerComponent.h"

// Sets default values for this component's properties
UDronePropellerComponent::UDronePropellerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

// Called every frame
void UDronePropellerComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Torque = GetPhysicsAngularVelocityInRadians();
}

void UDronePropellerComponent::InitializeComponent()
{
	SetSimulatePhysics(true);
	SetMassOverrideInKg(NAME_None, PropellorMass);
}

void UDronePropellerComponent::MoveUp(float InForce)
{
	FVector direction_vector = FVector::ZeroVector;
	switch (TorqueDirection)
	{
	case ETorqueDirection::X:
		direction_vector = GetForwardVector();
		break;
	case ETorqueDirection::Y:
		direction_vector = GetUpVector();
		break;
	case ETorqueDirection::Z:
		direction_vector = GetRightVector();
		break;
	default:
		break;
	}
	PropellerTorque = FVector::ZeroVector;
	PropellerTorque = direction_vector * InForce;
	PropellerTorque *= TorqueAcceleration;
	PropellerTorque *= GetMass();
	PropellerTorque *= PropellorPower;
	ApplyTorque(PropellerTorque);
}

void UDronePropellerComponent::ApplyTorque(const FVector& InTorque)
{
	AddAngularImpulseInRadians(InTorque);
}

