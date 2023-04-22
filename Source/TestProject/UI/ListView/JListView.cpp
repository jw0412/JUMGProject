#include "UI/ListView/JListView.h"

UJListView::UJListView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsFocusable = true;
	EntrySpacing = 10.f;
	WheelScrollMultiplier = 1.f;
	bEnableScrollAnimation = true;
	bReturnFocusToSelection = false;
	bClearSelectionOnClick = true;
	Orientation = EOrientation::Orient_Vertical;
	ConsumeMouseWheel = EConsumeMouseWheel::WhenScrollingPossible;
}
