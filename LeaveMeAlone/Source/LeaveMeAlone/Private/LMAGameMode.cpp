//  LeaveMeAlone Game by Netologiya. All RightsReserved.


#include "LMAGameMode.h"
#include "Player/LMADefaultCharacter.h"
#include "Player/LMAPLayerController.h"

ALMAGameMode::ALMAGameMode()
{
	DefaultPawnClass = ALMADefaultCharacter::StaticClass();
	PlayerControllerClass = ALMAPlayerController::StaticClass();

}
