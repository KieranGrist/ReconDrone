// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DroneEngineComponent.generated.h"

class ADronePawn;

/**
 *
 */
UCLASS()
class RECONDRONE_API UDroneEngineComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:
	UDroneEngineComponent();

	// Settable properties
	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float Acceleration = 500.0f;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float RotationAcceleration = 500.0f;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float Deceleration = 500.0f;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float Mass = 1;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float LinearDamping = 6;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float AngularDamping = 6;

	UPROPERTY(EditAnywhere,  Category = "Drone Engine")
	float EnginePower = 1;

	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void InitializeComponent() override;

	// 1 is maximum 0 is minimum
	void MoveUp(float InForce);

	// Adjust the drones
	void RotatePitch(float InForce);

	// Adjust the drones Yaw 
	void RotateYaw(float InForce);

	// Adjust the drones Roll
	void RotateRoll(float InForce);
	
	void StabiliseRotation();

protected:
	//Debug
	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector	UpForce;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector RightForce;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector ForwardForce;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector HoverForce;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector	YawTorque;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector PitchTorque;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector RollTorque;
	
	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector Velocity;
	
	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	FVector Torque;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "Drone Engine|Debug")
	float RotationSpeed;

	void Hover();
	void ApplyForce(const FVector& InForce, bool InAccelerationChange = false);
	void ApplyTorque(const FVector& InTorque, bool InAccelerationChange = false);
	void UpdateVelocity();
	void UpdateSpeed();
	void ResetForces();
	void UpdateMass();
};
