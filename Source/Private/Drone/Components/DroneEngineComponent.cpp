// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/Components/DroneEngineComponent.h"
#include "Kismet/KismetMathLibrary.h"


UDroneEngineComponent::UDroneEngineComponent()
{
	PrimaryComponentTick.bCanEverTick = true;
}

void UDroneEngineComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	Hover();
}

void UDroneEngineComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetMassOverrideInKg(NAME_None, Mass);
	BodyMass = GetMass();
}

void UDroneEngineComponent::MoveUp(float InForce)
{
	EngineForce = GetUpVector() * InForce * Acceleration;
	EngineForce *= BodyMass;
	EngineForce *= EnginePower;
	ApplyForce(EngineForce);
	GetWorld()->GetTimerManager().SetTimer(ResetForcesTimer, this, &UDroneEngineComponent::ResetForces, 0.4f, false);
}

float UDroneEngineComponent::GetAcceleration() const
{
	return Acceleration;
}

void UDroneEngineComponent::SetAcceleration(float InAcceleration)
{
	Acceleration = InAcceleration;
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
	return EngineForce;
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

void UDroneEngineComponent::ApplyForce(const FVector& InForce)
{
	// this component is usually a child of drone_mesh, lets see if we can get it
	UStaticMeshComponent* drone_mesh = Cast<UStaticMeshComponent>(GetAttachParent());
	if (drone_mesh)
		drone_mesh->AddForceAtLocation(InForce, GetComponentLocation());
	else
		AddForce(InForce);
}


void UDroneEngineComponent::ResetForces()
{
	EngineForce = FVector::ZeroVector;
	HoverForce = FVector::ZeroVector;
}
