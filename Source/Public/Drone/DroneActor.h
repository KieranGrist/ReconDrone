// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "InputActionValue.h"
#include "DroneActor.generated.h"

class UDroneMovementComponent;

UCLASS()
class RECONDRONE_API ADroneActor : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADroneActor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* DroneMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDroneMovementComponent* MovementComponent;

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotatePitchAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateYawAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* RotateRollAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* MoveUpAction;
	
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = Input, meta = (AllowPrivateAccess = "true"))
	class UInputAction* StabiliseRotationAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	// Collision event handler
	UFUNCTION()
	void OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void RotatePitch(const FInputActionValue& InInputActionValue);
	void RotateRoll(const FInputActionValue& InInputActionValue);
	void RotateYaw(const FInputActionValue& InInputActionValue);
	void MoveUp(const FInputActionValue& InInputActionValue);
	void StabiliseRotation(const FInputActionValue& InInputActionValue);
};
