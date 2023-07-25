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
	PitchTorque = FVector(0, InForce * RotationAcceleration, 0);
	ApplyTorque(PitchTorque);
}

void UDroneMovementComponent::RotateYaw(float InForce)
{
	YawTorque = FVector(0, 0, InForce * RotationAcceleration);
	ApplyTorque(YawTorque);
}

void UDroneMovementComponent::RotateRoll(float InForce)
{
	RollTorque = FVector(InForce * RotationAcceleration, 0, 0);
	ApplyTorque(RollTorque);
}

void UDroneMovementComponent::Hover()
{
	HoverForce = GetOwner()->GetActorUpVector() * -GetGravityZ();
	ApplyForce(HoverForce);
}

void UDroneMovementComponent::ApplyForce(const FVector& Force)
{
	// Get the Primitive Component and add the force
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		PrimitiveComp->AddForce(Force);
	}
}

void UDroneMovementComponent::ApplyTorque(const FVector& InTorque)
{
	UPrimitiveComponent* PrimitiveComp = Cast<UPrimitiveComponent>(UpdatedComponent);
	if (PrimitiveComp)
	{
		PrimitiveComp->AddTorqueInRadians(InTorque);
	}
}

void UDroneMovementComponent::UpdateVelocity()
{
	Velocity = UpdatedComponent->GetComponentVelocity();
}

void UDroneMovementComponent::UpdateSpeed()
{
	Speed = Velocity.Size();
	Speed /= 100;
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

