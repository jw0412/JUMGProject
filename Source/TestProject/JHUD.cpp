#include "JHUD.h"
#include "Manager/JWidgetManager.h"

void AJHUD::BeginPlay()
{
	Super::BeginPlay();

	JWIDGET_MGR().CreateMainHUDWidget(this);
}

void AJHUD::Destroyed()
{
	Super::Destroyed();

}
