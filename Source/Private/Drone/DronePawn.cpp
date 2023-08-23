// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/DronePawn.h"
#include "Drone/Components/DroneDamageHandlingComponent.h"
#include "Drone/Components/DroneEnergyComponent.h"
#include "Drone/Components/DroneEngineComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"
#include "Drone/Components/DronePropellerComponent.h"

ADronePawn::ADronePawn()
{
	PrimaryActorTick.bCanEverTick = true;

	DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
	DroneMesh->SetCollisionProfileName("BlockAll");
	DroneMesh->SetSimulatePhysics(true);
	DroneMesh->SetMassOverrideInKg(NAME_None, Mass);
	DroneMesh->SetNotifyRigidBodyCollision(true);
	SetRootComponent(DroneMesh);

	DamageHandlingComponent = CreateDefaultSubobject<UDroneDamageHandlingComponent>(TEXT("DamageHandlingComponent"));
	EnergyComponent = CreateDefaultSubobject<UDroneEnergyComponent>(TEXT("EnergyComponent"));
	MainDronePropeller = CreateDefaultSubobject<UDronePropellerComponent>(TEXT("MainDronePropeller"));

	MainDronePropeller->SetupAttachment(RootComponent);

	DroneMesh->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
	MainDronePropeller->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);

	// Set default auto possess player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	// This should always be true
	DroneMesh->SetSimulatePhysics(true);

	MainDronePropeller->SetLinearDamping(LinearDamping);
	MainDronePropeller->SetAngularDamping(AngularDamping);
	MainDronePropeller->InitializeComponent();

	DroneMesh->SetMassOverrideInKg(NAME_None, Mass);
	DroneMesh->SetLinearDamping(LinearDamping);
	DroneMesh->SetAngularDamping(AngularDamping);
	BodyMass = DroneMesh->GetMass();

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	UpdateVelocity();
	UpdateSpeed();
}

float ADronePawn::GetRotationSpeed() const
{
	return RotationSpeed;
}

float ADronePawn::GetSpeed() const
{
	return Speed;
}

const FVector& ADronePawn::GetTorque() const
{
	return Torque;
}

float ADronePawn::GetAngularDamping() const
{
	return AngularDamping;
}

void ADronePawn::SetAngularDamping(float InAngularDamping)
{
	AngularDamping = InAngularDamping;
}

float ADronePawn::GetLinearDamping() const
{
	return AngularDamping;
}

void ADronePawn::SetLinearDamping(float InLinearDamping)
{
	LinearDamping = InLinearDamping;
}

float ADronePawn::GetMass() const
{
	return Mass;
}

void ADronePawn::SetMass(float InMass)
{
	DroneMesh->SetMassOverrideInKg(NAME_None, InMass);
}

float ADronePawn::GetUnitMultiplier() const
{
	return UnitMultiplier;
}

void ADronePawn::UpdateVelocity()
{
	Velocity = DroneMesh->GetPhysicsLinearVelocity();
	Torque = DroneMesh->GetPhysicsAngularVelocityInRadians();
}

void ADronePawn::UpdateSpeed()
{
	Speed = Velocity.Size();
	RotationSpeed = Torque.Size();
}

void ADronePawn::OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

void ADronePawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
	{
		EnhancedInputComponent->BindAction(RotatePitchAction, ETriggerEvent::Triggered, this, &ADronePawn::RotatePitch);
		EnhancedInputComponent->BindAction(RotateYawAction, ETriggerEvent::Triggered, this, &ADronePawn::RotateYaw);
		EnhancedInputComponent->BindAction(RotateRollAction, ETriggerEvent::Triggered, this, &ADronePawn::RotateRoll);
		EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &ADronePawn::MoveUp);
		EnhancedInputComponent->BindAction(StabiliseRotationAction, ETriggerEvent::Triggered, this, &ADronePawn::StabiliseRotation);
	}
}

void ADronePawn::RotatePitch(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();

	if (value < 0)
	{

	}
	else
	{

	}
}

void ADronePawn::RotateRoll(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	if (value < 0)
	{

	}
	else
	{

	}

}

void ADronePawn::RotateYaw(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	if (value < 0)
	{

	}
	else
	{

	}
}

void ADronePawn::MoveUp(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	MainDronePropeller->MoveUp(value);
}

void ADronePawn::StabiliseRotation(const FInputActionValue& InInputActionValue)
{
	/*
	// Get the current rotation of the drone
	FRotator CurrentRotation = GetActorRotation();

	// Calculate the new rotation without pitch and roll
	FRotator NewRotation = FRotator(0.0f, CurrentRotation.Yaw, 0.0f);

	// Apply a torque force to the component to make it align with the new rotation
	FVector TorqueForce = (NewRotation - CurrentRotation).Quaternion().GetNormalized().GetRotationAxis() * RotationAcceleration;

	if (CurrentRotation.Equals(NewRotation, .2))
	{
		GetOwner()->SetActorRotation(NewRotation);
		ApplyTorque(FVector::ZeroVector, true);
		return;
	}
	ApplyTorque(TorqueForce);
	*/
}
