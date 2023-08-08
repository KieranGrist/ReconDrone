// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/Components/DroneEngineComponent.h"
#include "Kismet/KismetMathLibrary.h"


UDroneEngineComponent::UDroneEngineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
	MaxSpeed = 1000.0f;
	Acceleration = 500.0f;
	Deceleration = 500.0f;
}

void UDroneEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	ResetForces();
	Hover();
	UpdateVelocity();
	UpdateSpeed();
}

void UDroneEngineComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetMassOverrideInKg(NAME_None, Mass);
	SetLinearDamping(LinearDamping);
	SetAngularDamping(AngularDamping);
	BodyMass = GetMass();
}

void UDroneEngineComponent::MoveUp(float InForce)
{

	// Cant go faster then max speed 
	if ((GetUpVector() * Velocity).Size() >= GetMaxSpeed())
		return;
	UpForce = GetUpVector() * InForce * Acceleration;
	UpForce *= BodyMass;
	UpForce *= EnginePower;
	ApplyForce(UpForce);
}


const FVector& UDroneEngineComponent::GetVelocity() const
{
	return Velocity;
}

const FVector& UDroneEngineComponent::GetTorque() const
{
	return Torque;
}

float UDroneEngineComponent::GetSpeed() const
{
	return Speed;
}

float UDroneEngineComponent::GetRotationSpeed() const
{
	return RotationSpeed;
}

float UDroneEngineComponent::GetMaxSpeed() const
{
	return MaxSpeed;
}

void UDroneEngineComponent::SetMaxSpeed(float InMaxSpeed)
{
	MaxSpeed = InMaxSpeed;
}

float UDroneEngineComponent::GetAcceleration() const
{
	return Acceleration;
}

void UDroneEngineComponent::SetAcceleration(float InAcceleration)
{
	Acceleration = InAcceleration;
}

float UDroneEngineComponent::GetRotationAcceleration() const
{
	return RotationAcceleration;
}

void UDroneEngineComponent::SetRotationAcceleration(float InRotationAcceleration)
{
	RotationAcceleration = InRotationAcceleration;
}

float UDroneEngineComponent::GetEnginePower() const
{
	return EnginePower;
}

void UDroneEngineComponent::SetEnginePower(float InEnginePower)
{
	EnginePower = InEnginePower;
}

const FVector& UDroneEngineComponent::GetUpForce() const
{
	return UpForce;
}

const FVector& UDroneEngineComponent::GetHoverForce() const
{
	return HoverForce;
}

void UDroneEngineComponent::Hover()
{
	FVector up_vector = GetUpVector();
	float gravity_z = -GetWorld()->GetGravityZ();
	HoverForce = up_vector * gravity_z;
	HoverForce *= BodyMass;
	HoverForce *= EnginePower;
	ApplyForce(HoverForce);
}

void UDroneEngineComponent::ApplyForce(const FVector& InForce, bool InSetForce)
{
	if (InSetForce)
		SetAllPhysicsLinearVelocity(InForce);
	else
		AddForce(InForce);
}

void UDroneEngineComponent::ApplyTorque(const FVector& InTorque, bool InSetTorque)
{
	if (InSetTorque)
		SetAllPhysicsAngularVelocityInRadians(InTorque);
	else
		AddTorqueInRadians(InTorque);
}

void UDroneEngineComponent::UpdateVelocity()
{
	Velocity = GetPhysicsLinearVelocity();
	Torque = GetPhysicsAngularVelocityInRadians();
}

void UDroneEngineComponent::UpdateSpeed()
{
	Speed = Velocity.Size();
	RotationSpeed = GetTorque().Size();
}

void UDroneEngineComponent::ResetForces()
{
	UpForce = FVector::ZeroVector;
	HoverForce = FVector::ZeroVector;
}
