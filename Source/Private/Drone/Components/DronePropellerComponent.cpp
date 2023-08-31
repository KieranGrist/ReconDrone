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
	CurrentRotationSpeed += DeltaTime * RotationAcceleration;
	CurrentRotationSpeed = FMath::Min(RotationSpeed, CurrentRotationSpeed);
	RotationPercentage = CurrentRotationSpeed / RotationSpeed;

	AddLocalRotation(FRotator(0, CurrentRotationSpeed, 0));
	Hover();
}

void UDronePropellerComponent::InitializeComponent()
{
	SetSimulatePhysics(false);
	SetMassOverrideInKg(NAME_None, PropellorMass);
}

void UDronePropellerComponent::Hover()
{
	FVector up_vector = GetUpVector();
	float gravity_z = -GetWorld()->GetGravityZ();
	FVector HoverForce = up_vector * gravity_z;
	HoverForce *= GetMass();
	HoverForce *= PropellorPower;
	HoverForce *= RotationPercentage;
	ApplyForce(HoverForce);
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
	PropellerTorque *= PropellorAcceleration;
	PropellerTorque *= GetMass();
	PropellerTorque *= PropellorPower;
	PropellerTorque *= RotationPercentage;
	ApplyForce(PropellerTorque);
}



void UDronePropellerComponent::ApplyForce(const FVector& InForce)
{
	// this component is usually a child of drone_mesh, lets see if we can get it
	UStaticMeshComponent* drone_mesh = Cast<UStaticMeshComponent>(GetAttachParent());
	if (drone_mesh)
		drone_mesh->AddForceAtLocation(InForce, GetComponentLocation());
	else
		AddForce(InForce);
}