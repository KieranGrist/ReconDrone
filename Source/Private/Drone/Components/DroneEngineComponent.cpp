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

	PrimitiveComponent = GetOwner()->FindComponentByClass<UPrimitiveComponent>();
	if (!PrimitiveComponent)
	{
		UE_LOG(LogTemp, Fatal, TEXT("UDroneMovementComponent::PrimitiveComponent is not set, the owner does not have a primitive component"));
		checkNoEntry();
		return;
	}

	PrimitiveComponent->SetMassOverrideInKg(NAME_None, Mass);
	PrimitiveComponent->SetLinearDamping(LinearDamping);
	PrimitiveComponent->SetAngularDamping(AngularDamping);
}

void UDroneEngineComponent::MoveUp(float InForce)
{
	// Cant go faster then max speed 
	if ((PrimitiveComponent->GetUpVector() * Velocity).Size() >= MaxSpeed)
		return;
	UpForce = PrimitiveComponent->GetUpVector() * InForce * Acceleration;
	UpForce *= EnginePower;
	ApplyForce(UpForce);
}

void UDroneEngineComponent::RotatePitch(float InForce)
{
	PitchTorque = PrimitiveComponent->GetRightVector() * InForce * RotationAcceleration;
	ApplyTorque(PitchTorque);
}

void UDroneEngineComponent::RotateYaw(float InForce)
{
	YawTorque = PrimitiveComponent->GetUpVector() * InForce * RotationAcceleration;
	ApplyTorque(YawTorque);
}

void UDroneEngineComponent::RotateRoll(float InForce)
{
	RollTorque = PrimitiveComponent->GetForwardVector() * InForce * RotationAcceleration;
	ApplyTorque(RollTorque);
}

void UDroneEngineComponent::StabiliseRotation()
{
	// Get the current rotation of the drone
	FRotator CurrentRotation = PrimitiveComponent->GetComponentRotation();

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
	FVector up_vector = PrimitiveComponent->GetUpVector();
	float gravity_z = -GetWorld()->GetGravityZ();
	HoverForce = up_vector * gravity_z;
	// If its ever more then 1 we will constantly go up, this is bad
	HoverForce *= FMath::Min(1.0f, EnginePower);
	ApplyForce(HoverForce);
}

void UDroneEngineComponent::ApplyForce(const FVector& InForce, bool InSetForce)
{
	if (InSetForce)
		PrimitiveComponent->SetAllPhysicsLinearVelocity(InForce);
	else
		PrimitiveComponent->AddForce(InForce);
}

void UDroneEngineComponent::ApplyTorque(const FVector& InTorque, bool InSetTorque)
{
	if (InSetTorque)
		PrimitiveComponent->SetAllPhysicsAngularVelocityInRadians(InTorque);
	else
		PrimitiveComponent->AddTorqueInRadians(InTorque);
}

void UDroneEngineComponent::UpdateVelocity()
{
	Velocity = PrimitiveComponent->GetPhysicsLinearVelocity();
	Torque = PrimitiveComponent->GetPhysicsAngularVelocityInRadians();
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
	Mass = PrimitiveComponent->GetMass();
}

