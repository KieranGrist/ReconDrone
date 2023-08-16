// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/DronePawn.h"
#include "Drone/Components/DroneDamageHandlingComponent.h"
#include "Drone/Components/DroneEnergyComponent.h"
#include "Drone/Components/DroneEngineComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Kismet/GameplayStatics.h"

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
	TopLeftEngine = CreateDefaultSubobject<UDroneEngineComponent>(TEXT("TopLeftEngine"));
	TopRightEngine = CreateDefaultSubobject<UDroneEngineComponent>(TEXT("TopRightEngine"));
	BottomLeftEngine = CreateDefaultSubobject<UDroneEngineComponent>(TEXT("BottomLeftEngine"));
	BottomRightEngine = CreateDefaultSubobject<UDroneEngineComponent>(TEXT("BottomRightEngine"));

	TopLeftEngine->SetupAttachment(RootComponent);
	TopRightEngine->SetupAttachment(RootComponent);
	BottomLeftEngine->SetupAttachment(RootComponent);
	BottomRightEngine->SetupAttachment(RootComponent);

	DroneMesh->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
	TopLeftEngine->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
	TopRightEngine->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
	BottomLeftEngine->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
	BottomRightEngine->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);

	// Set default auto possess player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	// This should always be true
	DroneMesh->SetSimulatePhysics(true);

	TopLeftEngine->SetLinearDamping(LinearDamping);
	TopRightEngine->SetLinearDamping(LinearDamping);
	BottomLeftEngine->SetLinearDamping(LinearDamping);
	BottomRightEngine->SetLinearDamping(LinearDamping);

	TopLeftEngine->SetAngularDamping(AngularDamping);
	TopRightEngine->SetAngularDamping(AngularDamping);
	BottomLeftEngine->SetAngularDamping(AngularDamping);
	BottomRightEngine->SetAngularDamping(AngularDamping);

	TopLeftEngine->InitializeComponent();
	TopRightEngine->InitializeComponent();
	BottomLeftEngine->InitializeComponent();
	BottomRightEngine->InitializeComponent();

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
	UpdateMass();
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

float ADronePawn::GetTotalDroneMass() const
{
	return TotalDroneMass;
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

void ADronePawn::UpdateMass()
{
	TotalDroneMass = DroneMesh->GetMass() + TopLeftEngine->GetMass() + TopRightEngine->GetMass() + BottomLeftEngine->GetMass() + BottomRightEngine->GetMass();
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
		TopLeftEngine->MoveUp(-value);
		TopRightEngine->MoveUp(-value);
		BottomLeftEngine->MoveUp(value);
		BottomRightEngine->MoveUp(value);
	}
	else
	{
		BottomLeftEngine->MoveUp(value);
		BottomRightEngine->MoveUp(value);
		TopLeftEngine->MoveUp(-value);
		TopRightEngine->MoveUp(-value);
	}
}

void ADronePawn::RotateRoll(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	if (value < 0)
	{
		TopLeftEngine->MoveUp(-value);
		BottomLeftEngine->MoveUp(-value);
		TopRightEngine->MoveUp(value);
		BottomRightEngine->MoveUp(value);
	}
	else
	{	TopLeftEngine->MoveUp(-value);
		BottomLeftEngine->MoveUp(-value);
		TopRightEngine->MoveUp(value);
		BottomRightEngine->MoveUp(value);
	}

}

void ADronePawn::RotateYaw(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	if (value < 0)
	{
		TopLeftEngine->MoveUp(-value);
		BottomRightEngine->MoveUp(-value);
		TopRightEngine->MoveUp(value);
		BottomLeftEngine->MoveUp(value);
	}
	else
	{
		TopLeftEngine->MoveUp(value);
		BottomRightEngine->MoveUp(value);
		TopRightEngine->MoveUp(-value);
		BottomLeftEngine->MoveUp(-value);
	}
}

void ADronePawn::MoveUp(const FInputActionValue& InInputActionValue)
{
	float value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	TopLeftEngine->MoveUp(value);
	TopRightEngine->MoveUp(value);
	BottomLeftEngine->MoveUp(value);
	BottomRightEngine->MoveUp(value);
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
