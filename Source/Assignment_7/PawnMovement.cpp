#include "PawnMovement.h"
#include "SpartaPlayerController.h"
#include "Components/CapsuleComponent.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputComponent.h"
#include "GameFramework/SpringArmComponent.h"

APawnMovement::APawnMovement()
{
	PrimaryActorTick.bCanEverTick = false;

	Collision = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Collision"));
	SetRootComponent(Collision);

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetupAttachment(Collision);

	SpringArmComp = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArmComp->SetupAttachment(Collision);
	SpringArmComp->TargetArmLength = 300.0f;
	SpringArmComp->bUsePawnControlRotation = true;

	CameraComp = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	CameraComp->SetupAttachment(SpringArmComp, USpringArmComponent::SocketName);
	CameraComp->bUsePawnControlRotation = false;
}

void APawnMovement::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if (UEnhancedInputComponent* EnhancedInput = Cast<UEnhancedInputComponent>(PlayerInputComponent))
	{
		if (ASpartaPlayerController* PlayerController = Cast<ASpartaPlayerController>(GetController()))
		{
			if (PlayerController->MoveAction)
			{
				EnhancedInput->BindAction(
					PlayerController->MoveAction,
					ETriggerEvent::Triggered,
					this,
					&APawnMovement::Move
				);
			}

			if (PlayerController->LookAction)
			{
				EnhancedInput->BindAction(
					PlayerController->LookAction,
					ETriggerEvent::Triggered,
					this,
					&APawnMovement::Look
				);
			}
		}
	}
}

void APawnMovement::Move(const FInputActionValue& Value)
{
	if (!Controller)
		return;

	const FVector2D MoveInput = Value.Get<FVector2D>();

	FVector ForwardMovement = FVector::ZeroVector;
	FVector RightMovement = FVector::ZeroVector;

	if (!FMath::IsNearlyZero(MoveInput.X))
		ForwardMovement = GetActorForwardVector() * MoveInput.X;

	if (!FMath::IsNearlyZero(MoveInput.Y))
		RightMovement = GetActorRightVector() * MoveInput.Y;

	FVector FinalMovement = ForwardMovement + RightMovement;
	AddActorLocalOffset(FinalMovement, true);
}
		

void APawnMovement::Look(const FInputActionValue& Value)
{
	const FVector2D LookInput = Value.Get<FVector2D>();

	FRotator CurrentRotation = GetActorRotation();

	if (!FMath::IsNearlyZero(LookInput.X))	
		CurrentRotation.Yaw += LookInput.X;

	if (!FMath::IsNearlyZero(LookInput.Y))
		CurrentRotation.Pitch = FMath::Clamp(CurrentRotation.Pitch - LookInput.Y, -45.0f, 45.0f);

	SetActorRotation(CurrentRotation);
}

