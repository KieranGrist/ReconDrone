// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "Components/ChildActorComponent.h"
#include "DronePawn.generated.h"

class UDroneEngineComponent;
class UDroneDamageHandlingComponent;
class UDroneEnergyComponent;

UCLASS()
class RECONDRONE_API ADronePawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADronePawn();


	UFUNCTION(BlueprintCallable)
	float GetRotationSpeed() const;

	UFUNCTION(BlueprintCallable)
	float GetSpeed() const;

	UFUNCTION(BlueprintCallable)
	const FVector& GetTorque() const;

	UFUNCTION(BlueprintCallable)
	float GetTotalDroneMass() const;

	UFUNCTION(BlueprintCallable)
	float GetAngularDamping() const;

	UFUNCTION(BlueprintCallable)
	void SetAngularDamping(float InAngularDamping);

	UFUNCTION(BlueprintCallable)
	float GetLinearDamping() const;

	UFUNCTION(BlueprintCallable)
	void SetLinearDamping(float InLinearDamping);

	UFUNCTION(BlueprintCallable)
	float GetMass() const;

	UFUNCTION(BlueprintCallable)
	void SetMass(float InMass);

	UFUNCTION(BlueprintCallable)
	float GetUnitMultiplier() const;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneEngine")
	UDroneEngineComponent* TopLeftEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneEngine")
	UDroneEngineComponent* TopRightEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneEngine")
	UDroneEngineComponent* BottomLeftEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DroneEngine")
	UDroneEngineComponent* BottomRightEngine;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DronePawn")
	UStaticMeshComponent* DroneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DronePawn")
	UDroneDamageHandlingComponent* DamageHandlingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "DronePawn")
	UDroneEnergyComponent* EnergyComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	// Collision event handler
	UFUNCTION()
	void OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	void RotatePitch(const FInputActionValue& InInputActionValue);
	void RotateRoll(const FInputActionValue& InInputActionValue);
	void RotateYaw(const FInputActionValue& InInputActionValue);
	void MoveUp(const FInputActionValue& InInputActionValue);
	void StabiliseRotation(const FInputActionValue& InInputActionValue);
	void UpdateVelocity();
	void UpdateSpeed();
	void UpdateMass();

	/** MappingContext */
	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotatePitchAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateYawAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateRollAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveUpAction;

	UPROPERTY(EditAnywhere, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* StabiliseRotationAction;

	UPROPERTY(EditAnywhere, Category = "DronePawn")
	float Mass = 1;

	UPROPERTY(EditAnywhere, Category = "DronePawn")
	float UnitMultiplier = 1;

	UPROPERTY(EditAnywhere, Category = "DroneEngine")
	float BodyMass = 1;

	UPROPERTY(EditAnywhere, Category = "DronePawn")
	float LinearDamping = 6;

	UPROPERTY(EditAnywhere, Category = "DronePawn")
	float AngularDamping = 6;

	UPROPERTY(VisibleAnywhere, Category = "DronePawn")
	float TotalDroneMass = 1;

	UPROPERTY(VisibleAnywhere, Category = "DronePawn|Debug")
	FVector Velocity;

	UPROPERTY(VisibleAnywhere, Category = "DronePawn|Debug")
	FVector Torque;

	UPROPERTY(VisibleAnywhere, Category = "DronePawn|Debug")
	float Speed;

	UPROPERTY(VisibleAnywhere, Category = "DronePawn|Debug")
	float RotationSpeed;
};
