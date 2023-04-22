#include "JGameMode.h"
#include "JHUD.h"
#include "Pawn/JPawn.h"
#include "Controller/JPlayerController.h"
#include "Manager/JWidgetManager.h"

AJGameMode::AJGameMode()
{	
	PlayerControllerClass = AJPlayerController::StaticClass();
	HUDClass = AJHUD::StaticClass();
	DefaultPawnClass = AJPawn::StaticClass();
}

AJGameMode::~AJGameMode()
{
	
}
