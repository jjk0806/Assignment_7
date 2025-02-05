#include "Flyer.h"

AFlyer::AFlyer()
{
	PrimaryActorTick.bCanEverTick = true;
}

void AFlyer::BeginPlay()
{
	Super::BeginPlay();
	
}

void AFlyer::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AFlyer::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}