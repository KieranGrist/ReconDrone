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

	UFUNCTION(BlueprintCallable)
	float GetMaxSpeed() const;

	UFUNCTION(BlueprintCallable)
	void SetMaxSpeed(float InMaxSpeed);

	UFUNCTION(BlueprintCallable)
	float GetAcceleration() const;

	UFUNCTION(BlueprintCallable)
	void SetAcceleration(float InAcceleration);

	UFUNCTION(BlueprintCallable)
	float GetRotationAcceleration() const;

	UFUNCTION(BlueprintCallable)
	void SetRotationAcceleration(float InRotationAcceleration);

	UFUNCTION(BlueprintCallable)
	float GetEnginePower() const;

	UFUNCTION(BlueprintCallable)
	void SetEnginePower(float InEnginePower);

	UFUNCTION(BlueprintCallable)
	const FVector& GetUpForce() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetRightForce() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetForwardForce() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetHoverForce() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetYawTorque() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetPitchTorque() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetRollTorque() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetVelocity() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetTorque() const;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetRotationSpeed() const;

protected:
	void Hover();
	void ApplyForce(const FVector& InForce, bool InAccelerationChange = false);
	void ApplyTorque(const FVector& InTorque, bool InAccelerationChange = false);
	void UpdateVelocity();
	void UpdateSpeed();
	void ResetForces();

	// Settable properties
	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float MaxSpeed = 1000.0f;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float Acceleration = 500.0f;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float RotationAcceleration = 500.0f;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float Deceleration = 500.0f;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float Mass = 1;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float BodyMass = 1;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float LinearDamping = 6;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float AngularDamping = 6;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float EnginePower = 1;

	//Debug Properties
	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector	UpForce;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector RightForce;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector ForwardForce;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector HoverForce;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector	YawTorque;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector PitchTorque;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector RollTorque;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector Torque;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	float RotationSpeed;
};
