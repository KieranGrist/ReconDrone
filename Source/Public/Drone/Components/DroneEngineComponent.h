// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
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

	void MoveUp(float InForce);

	UFUNCTION(BlueprintCallable)
	float GetAcceleration() const;

	UFUNCTION(BlueprintCallable)
	void SetAcceleration(float InAcceleration);

	UFUNCTION(BlueprintCallable)
	float GetEnginePower() const;

	UFUNCTION(BlueprintCallable)
	void SetEnginePower(float InEnginePower);

	UFUNCTION(BlueprintCallable)
	const FVector& GetUpForce() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetHoverForce() const;
protected:
	UFUNCTION()
	void Hover();

	UFUNCTION()
	void ApplyForce(const FVector& InForce);

	UFUNCTION()
	void ResetForces();

	FTimerHandle ResetForcesTimer;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float Acceleration = 500.0f;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float Mass = 1;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float BodyMass = 1;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float EnginePower = 1;

	//Debug Properties
	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector	EngineForce;

	UPROPERTY(VisibleAnywhere, Category = "DroneEngine|Debug")
	FVector HoverForce;
};
