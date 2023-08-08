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
	DroneMesh->SetMassOverrideInKg(NAME_None, 1);
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

	//Add Input Mapping Context
	if (APlayerController* PlayerController = Cast<APlayerController>(Controller))
	{
		if (UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer()))
		{
			Subsystem->AddMappingContext(DefaultMappingContext, 0);
		}
	}
}

void ADronePawn::OnDroneHit(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	// Check if the drone collided with something
	if (OtherActor != nullptr && OtherActor != this)
	{
		// Restart the level when the drone collides with something
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}
}

// Called every frame
void ADronePawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

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
