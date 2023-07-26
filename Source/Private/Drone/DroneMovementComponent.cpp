// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/DroneMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"


UDroneMovementComponent::UDroneMovementComponent()
{
	MaxSpeed = 1000.0f;
	Acceleration = 500.0f;
	Deceleration = 500.0f;
}

void UDroneMovementComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	//ResetForces();
	Hover();
	UpdateVelocity();
	UpdateSpeed();
	UpdateMass();
}

void UDroneMovementComponent::InitializeComponent()
{
	Super::InitializeComponent();
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		PrimitiveComp->SetMassOverrideInKg(NAME_None, Mass);
		PrimitiveComp->SetLinearDamping(LinearDamping);
		PrimitiveComp->SetAngularDamping(AngularDamping);
	}
}

void UDroneMovementComponent::MoveUp(float InForce)
{
	// Cant go faster then max speed 
	if ((GetOwner()->GetActorUpVector() * Velocity).Size() >= MaxSpeed)
		return;
	UpForce = GetOwner()->GetActorUpVector() * InForce * Acceleration;
	ApplyForce(UpForce);
}

void UDroneMovementComponent::RotatePitch(float InForce)
{
	PitchTorque = GetOwner()->GetActorRightVector() * InForce * RotationAcceleration;
	ApplyTorque(PitchTorque);
}

void UDroneMovementComponent::RotateYaw(float InForce)
{
	YawTorque = GetOwner()->GetActorUpVector() * InForce * RotationAcceleration;
	ApplyTorque(YawTorque);
}

void UDroneMovementComponent::RotateRoll(float InForce)
{
	RollTorque = GetOwner()->GetActorForwardVector() * InForce * RotationAcceleration;
	ApplyTorque(RollTorque);
}

void UDroneMovementComponent::StabiliseRotation()
{
	if (!UpdatedComponent || !PawnOwner)
	{
		return;
	}

	// Get the current rotation of the drone
	FRotator CurrentRotation = UpdatedComponent->GetComponentRotation();

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

void UDroneMovementComponent::Hover()
{
	HoverForce = GetOwner()->GetActorUpVector() * -GetGravityZ();
	ApplyForce(HoverForce);
}

void UDroneMovementComponent::ApplyForce(const FVector& InForce, bool InSetForce)
{
	// Get the Primitive Component and add the force
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		if (InSetForce)
			PrimitiveComp->SetAllPhysicsLinearVelocity(InForce);
		else
			PrimitiveComp->AddForce(InForce);
	}
}

void UDroneMovementComponent::ApplyTorque(const FVector& InTorque, bool InSetTorque)
{
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		if (InSetTorque)
			PrimitiveComp->SetAllPhysicsAngularVelocityInRadians(InTorque);
		else
			PrimitiveComp->AddTorqueInRadians(InTorque);
	}
}

void UDroneMovementComponent::UpdateVelocity()
{
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		Velocity = PrimitiveComp->GetPhysicsLinearVelocity();
		Torque = PrimitiveComp->GetPhysicsAngularVelocityInRadians();
	}
}

void UDroneMovementComponent::UpdateSpeed()
{
	Speed = Velocity.Size();
	RotationSpeed = Torque.Size();
}

void UDroneMovementComponent::ResetForces()
{
	UpForce = FVector::ZeroVector;
	RightForce = FVector::ZeroVector;
	ForwardForce = FVector::ZeroVector;
	HoverForce = FVector::ZeroVector;
}

void UDroneMovementComponent::UpdateMass()
{
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		Mass = PrimitiveComp->GetMass();
	}
}

