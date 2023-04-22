#include "GameInstance/JGameInstance.h"
#include "Manager/JWidgetManager.h"

void UJGameInstance::Init()
{
	Super::Init();
}

void UJGameInstance::Shutdown()
{
	Super::Shutdown();

	JWIDGET_MGR().ShutDown();
}