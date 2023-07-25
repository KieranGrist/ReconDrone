// Fill out your copyright notice in the Description page of Project Settings.


#include "Drone/DroneActor.h"
#include "Drone/DroneMovementComponent.h"
#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"


ADroneActor::ADroneActor()
{
    PrimaryActorTick.bCanEverTick = true;
    RootComponent = DroneMesh;

    DroneMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("DroneMesh"));
    DroneMesh->SetupAttachment(RootComponent);
    DroneMesh->SetSimulatePhysics(true);
    DroneMesh->SetMassOverrideInKg(NAME_None, 1);
    MovementComponent = CreateDefaultSubobject<UDroneMovementComponent>(TEXT("MovementComponent"));
  
    // Set default auto possess player
    AutoPossessPlayer = EAutoReceiveInput::Player0;
}

// Called when the game starts or when spawned
void ADroneActor::BeginPlay()
{
	Super::BeginPlay();
    // This should always be true
    DroneMesh->SetSimulatePhysics(true);

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
void ADroneActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADroneActor::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
    Super::SetupPlayerInputComponent(PlayerInputComponent);
    if (UEnhancedInputComponent* EnhancedInputComponent = CastChecked<UEnhancedInputComponent>(PlayerInputComponent))
    {
        EnhancedInputComponent->BindAction(RotatePitchAction, ETriggerEvent::Triggered, this, &ADroneActor::RotatePitch);
        EnhancedInputComponent->BindAction(RotateYawAction, ETriggerEvent::Triggered, this, &ADroneActor::RotateYaw);
        EnhancedInputComponent->BindAction(RotateRollAction, ETriggerEvent::Triggered, this, &ADroneActor::RotateRoll);
        EnhancedInputComponent->BindAction(MoveUpAction, ETriggerEvent::Triggered, this, &ADroneActor::MoveUp);
    }
}

void ADroneActor::RotatePitch(const FInputActionValue& InInputActionValue)
{
    if (MovementComponent)
    {
        float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
        MovementComponent->RotatePitch(value);
    }
}

void ADroneActor::RotateRoll(const FInputActionValue& InInputActionValue)
{
    if (MovementComponent)
    {
        float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
        MovementComponent->RotateRoll(value);
    }
}

void ADroneActor::RotateYaw(const FInputActionValue& InInputActionValue)
{
    // Call the MoveRight function in the UDroneMovementComponent
    if (MovementComponent)
    {
        float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
        MovementComponent->RotateYaw(value);
    }
}

void ADroneActor::MoveUp(const FInputActionValue& InInputActionValue)
{
    // Call the MoveRight function in the UDroneMovementComponent
    if (MovementComponent)
    {
        float  value = InInputActionValue.Get<FInputActionValue::Axis1D>();
        MovementComponent->MoveUp(value);
    }
}
