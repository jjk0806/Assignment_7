#include "Sparta_GameMode.h"
#include "PawnMovement.h"
#include "SpartaPlayerController.h"

ASparta_GameMode::ASparta_GameMode()
{
	DefaultPawnClass = APawnMovement::StaticClass();
	PlayerControllerClass = ASpartaPlayerController::StaticClass();
}