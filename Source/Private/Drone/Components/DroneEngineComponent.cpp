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
	//ResetForces();
	Hover();
	UpdateVelocity();
	UpdateSpeed();
	UpdateMass();
}

void UDroneEngineComponent::InitializeComponent()
{
	Super::InitializeComponent();

	SetMassOverrideInKg(NAME_None, Mass);
	SetLinearDamping(LinearDamping);
	SetAngularDamping(AngularDamping);
}

void UDroneEngineComponent::MoveUp(float InForce)
{
	// Cant go faster then max speed 
	if ((GetUpVector() * Velocity).Size() >= MaxSpeed)
		return;
	UpForce = GetUpVector() * InForce * Acceleration;
	UpForce *= EnginePower;
	ApplyForce(UpForce);
}

void UDroneEngineComponent::RotatePitch(float InForce)
{
	PitchTorque = GetRightVector() * InForce * RotationAcceleration;
	ApplyTorque(PitchTorque);
}

void UDroneEngineComponent::RotateYaw(float InForce)
{
	YawTorque = GetUpVector() * InForce * RotationAcceleration;
	ApplyTorque(YawTorque);
}

void UDroneEngineComponent::RotateRoll(float InForce)
{
	RollTorque = GetForwardVector() * InForce * RotationAcceleration;
	ApplyTorque(RollTorque);
}

void UDroneEngineComponent::StabiliseRotation()
{
	// Get the current rotation of the drone
	FRotator CurrentRotation = GetComponentRotation();

	// Calculate the new rotation without pitch and roll
	FRotator NewRotation = FRotator(0.0f, CurrentRotation.Yaw, 0.0f);

	// Apply a torque force to the component to make it align with the new rotation
	FVector TorqueForce = (NewRotation - CurrentRotation).Quaternion().GetNormalized().GetRotationAxis() * RotationAcceleration;

	if (CurrentRotation.Equals(NewRotation, .2))
	{
		GetOwner()->SetActorRotation(NewRotation);
		ApplyTorque(FVector::ZeroVector, true);
		return;
	}
	ApplyTorque(TorqueForce);
}

void UDroneEngineComponent::Hover()
{
	FVector up_vector = GetUpVector();
	float gravity_z = -GetWorld()->GetGravityZ();
	HoverForce = up_vector * gravity_z;
	// If its ever more then 1 we will constantly go up, this is bad
	HoverForce *= FMath::Min(1.0f, EnginePower);
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
	RotationSpeed = Torque.Size();
}

void UDroneEngineComponent::ResetForces()
{
	UpForce = FVector::ZeroVector;
	RightForce = FVector::ZeroVector;
	ForwardForce = FVector::ZeroVector;
	HoverForce = FVector::ZeroVector;
}

void UDroneEngineComponent::UpdateMass()
{
	Mass = GetMass();
}

