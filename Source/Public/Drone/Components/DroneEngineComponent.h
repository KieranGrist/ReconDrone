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
class RECONDRONE_API UDroneEngineComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	UDroneEngineComponent();

	// The primitive component to apply forces and torques 
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	UPrimitiveComponent* PrimitiveComponent;

	// Settable properties
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float Acceleration = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float RotationAcceleration = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float Deceleration = 500.0f;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float Mass = 1;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float LinearDamping = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
	float AngularDamping = 6;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Drone Movement")
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
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector	UpForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector RightForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector ForwardForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector HoverForce;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector	YawTorque;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector PitchTorque;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector RollTorque;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector Velocity;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	FVector Torque;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	float Speed;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Drone Movement|Debug")
	float RotationSpeed;

	void Hover();
	void ApplyForce(const FVector& InForce, bool InAccelerationChange = false);
	void ApplyTorque(const FVector& InTorque, bool InAccelerationChange = false);
	void UpdateVelocity();
	void UpdateSpeed();
	void ResetForces();
	void UpdateMass();
};
