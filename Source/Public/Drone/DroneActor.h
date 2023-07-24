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

   UPROPERTY(EditAnywhere)
    UStaticMeshComponent* DroneMesh;

    UPROPERTY(EditAnywhere)
    UDroneMovementComponent* MovementComponent; 

	/** MappingContext */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputMappingContext* DefaultMappingContext;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveForwardAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveRightAction;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category=Input, meta=(AllowPrivateAccess = "true"))
	class UInputAction* MoveUpAction;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	void MoveForward(const FInputActionValue& InInputActionValue);
	void MoveRight(const FInputActionValue& InInputActionValue);
	void MoveUp(const FInputActionValue& InInputActionValue);
};