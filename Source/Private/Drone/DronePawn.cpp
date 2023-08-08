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
	DroneMesh->OnComponentHit.AddUniqueDynamic(this, &ADronePawn::OnDroneHit);
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

	// Set default auto possess player
	AutoPossessPlayer = EAutoReceiveInput::Player0;
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

// Called when the game starts or when spawned
void ADronePawn::BeginPlay()
{
	Super::BeginPlay();
	// This should always be true
	DroneMesh->SetSimulatePhysics(true);
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
	float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
}

void ADronePawn::RotateRoll(const FInputActionValue& InInputActionValue)
{
	float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
}

void ADronePawn::RotateYaw(const FInputActionValue& InInputActionValue)
{
	float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
}

void ADronePawn::MoveUp(const FInputActionValue& InInputActionValue)
{
	float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
	TopLeftEngine->MoveUp(value);
	TopRightEngine->MoveUp(value);
	BottomLeftEngine->MoveUp(value);
	BottomRightEngine->MoveUp(value);
}

void ADronePawn::StabiliseRotation(const FInputActionValue& InInputActionValue)
{
	TopLeftEngine->StabiliseRotation();
	TopRightEngine->StabiliseRotation();
	BottomLeftEngine->StabiliseRotation();
	BottomRightEngine->StabiliseRotation();
}
