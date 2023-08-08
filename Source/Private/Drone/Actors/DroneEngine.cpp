// Fill out your copyright notice in the Description page of Project Settings.
#include "Drone/Actors/DroneEngine.h"
#include "Drone/Components/DroneEngineComponent.h"
#include "Drone/Components/DroneDamageHandlingComponent.h"
#include "Drone/Components/DroneEnergyComponent.h"

// Sets default values
ADroneEngine::ADroneEngine()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
    RootComponent = EngineMesh;

    EngineMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
    EngineMesh->SetupAttachment(RootComponent);
    EngineMesh->SetCollisionProfileName("BlockAll");
    EngineMesh->SetSimulatePhysics(true);
    EngineMesh->SetMassOverrideInKg(NAME_None, 1);
    EngineMesh->SetNotifyRigidBodyCollision(true);
    EngineMesh->OnComponentHit.AddUniqueDynamic(this, &ADroneEngine::OnDroneHit);

    EngineComponent = CreateDefaultSubobject<UDroneEngineComponent>(TEXT("EngineComponent"));
    DamageHandlingComponent = CreateDefaultSubobject<UDroneDamageHandlingComponent>(TEXT("DamageHandlingComponent"));
    EnergyComponent = CreateDefaultSubobject<UDroneEnergyComponent>(TEXT("EnergyComponent"));
}

// Called when the game starts or when spawned
void ADroneEngine::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADroneEngine::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroneEngine::OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

