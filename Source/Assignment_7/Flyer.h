#pragma once
#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Flyer.generated.h"

UCLASS()
class ASSIGNMENT_7_API AFlyer : public ACharacter
{
	GENERATED_BODY()

public:
	AFlyer();

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

private:
	float Acceleration = 30.0f;
	float MaxSpeed = 4000.0f;
	float MinSpeed = 500.0f;

	float CurrentForwardSpeed;

	float CurrentYawSpeed;
	float CurrentPitchSpeed;
	float CurrentRollSpeed;
};
