// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PawnMovementComponent.h"
#include "DroneMovementComponent.generated.h"

class ADroneActor;

/**
 * 
 */
UCLASS()
class RECONDRONE_API UDroneMovementComponent : public UPawnMovementComponent
{
    GENERATED_BODY()

public:
    UDroneMovementComponent();

    // Settable properties
    UPROPERTY(EditAnywhere, Category = "Drone Movement")
    float MaxSpeed = 1000.0f;

    UPROPERTY(EditAnywhere, Category = "Drone Movement")
    float Acceleration = 500.0f;

    UPROPERTY(EditAnywhere, Category = "Drone Movement")
    float Deceleration = 500.0f;
    
    //Debug
    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    FVector	UpForce;

    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    FVector RightForce;

    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    FVector ForwardForce;
   
    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    FVector HoverForce;

    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    float Speed;

    UPROPERTY(VisibleAnywhere, Category = "Drone Movement|Debug")
    float Mass;

    virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

    // 1 is maximum 0 is minimum
    void MoveUp(float InForce);
    void MoveForward(float InForce);
    void MoveRight(float InForce);
 
    void Hover();
    void ApplyForce(const FVector& InForce);
    void UpdateVelocity();
    void UpdateSpeed();
    void HandleMaximumSpeed();
    void ResetForces();
    void UpdateMass();
};
