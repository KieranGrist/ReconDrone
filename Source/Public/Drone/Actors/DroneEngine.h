// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DroneEngine.generated.h"

class UDroneEngineComponent;
class UDroneDamageHandlingComponent;
class UDroneEnergyComponent;

UCLASS()
class RECONDRONE_API ADroneEngine : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADroneEngine();
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UStaticMeshComponent* EngineMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDroneEngineComponent* EngineComponent;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDroneDamageHandlingComponent* DamageHandlingComponent;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	UDroneEnergyComponent* EnergyComponent;
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Collision event handler
	UFUNCTION()
	void OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

};
