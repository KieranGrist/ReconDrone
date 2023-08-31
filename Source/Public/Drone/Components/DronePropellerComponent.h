// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/StaticMeshComponent.h"
#include "DronePropellerComponent.generated.h"

UENUM(BlueprintType)
enum class ETorqueDirection : uint8
{
	X,
	Y,
	Z
};


UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RECONDRONE_API UDronePropellerComponent : public UStaticMeshComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UDronePropellerComponent();

	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void InitializeComponent() override;

	void MoveUp(float InForce);
protected:
	void ApplyForce(const FVector& InForce);
	void Hover();

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	float PropellorPower;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	float PropellorAcceleration;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	float PropellorMass = 1;

	UPROPERTY(EditAnywhere, Category = "DronePropeller")
	float RotationSpeed = 100;

	UPROPERTY(EditAnywhere, Category = "DronePropeller")
	float RotationAcceleration = 1;

	UPROPERTY(EditAnywhere, Category = "DronePropeller")
	float CurrentRotationSpeed = 0;
	
	UPROPERTY(EditAnywhere, Category = "DronePropeller")
	float RotationPercentage = 0;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	bool Clockwise = true;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	FVector PropellerTorque;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	ETorqueDirection TorqueDirection;

	UPROPERTY(EditAnywhere, Category="DronePropeller")
	FVector Torque;
};
