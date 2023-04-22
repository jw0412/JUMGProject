#include "UI/GameStore/GameStoreItemWidget.h"

#include "Components/Image.h"
#include "Components/Border.h"
#include "Components/TextBlock.h"

#include "UI/GameStore/GameStoreItemObject.h"

void UGameStoreItemWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	Border_FocusBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UGameStoreItemWidget::NativeConstruct()
{
	Super::NativeConstruct();

}

void UGameStoreItemWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

void UGameStoreItemWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
	UGameStoreItemObject* StoreItemObj = Cast<UGameStoreItemObject>(ListItemObject);
	if (StoreItemObj)
	{
		Text_ItemName->SetText(FText::FromString(StoreItemObj->GetItemName()));
		OnStoreItemFocuseChangedCallback(StoreItemObj->IsItemFocus());
	}
}

void UGameStoreItemWidget::OnStoreItemFocuseChangedCallback(bool bFocus)
{
	if (bFocus)
	{
		this->SetKeyboardFocus();
	}

	Border_FocusBox->SetVisibility(bFocus ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

