#include "UI/GameStore/GameStoreItemObject.h"
#include "Utility/JLogUtility.h"
#include "Manager/JWidgetManager.h"

void UGameStoreItemObject::SetData(UObject* NewOwningWidget, const FString& NewItemName, bool bNewItemFocus)
{
	OwningWidget = NewOwningWidget;
	ItemName = NewItemName;
	bItemFocus = bNewItemFocus;
}

FString UGameStoreItemObject::GetItemName()
{
	return ItemName;
}

void UGameStoreItemObject::CreateItemPurchasePopup()
{
	AsyncTask(ENamedThreads::GameThread, [=]
	{
		const FString ItemPuchaseDescription = FString::Printf(TEXT("[%s] 아이템을 구매하시겠습니까?"), *ItemName);
		JWIDGET_MGR().CreateAlertDialogWidget(OwningWidget, TEXT("아이템 구매"), ItemPuchaseDescription, FVector2D(800.f, 450.f), FOnJDialogResult::CreateLambda([=](bool bConfirm)
		{
			const FColor DesiredLogMsgColor = bConfirm ? FColor::Cyan : FColor::Yellow;
			const EJLogLevel DesiredLogLevel = bConfirm ? EJLogLevel::Display : EJLogLevel::Warning;
			const FString PurchaseResultString = bConfirm ? TEXT("성공") : TEXT("실패");
			const FString ItemPurchaseResultString = FString::Printf(TEXT("[%s] 아이템을 구매에 %s하셨습니다."), *ItemName, *PurchaseResultString);
			FJLogUtility::PrintJScreenDebugLog(1.f, DesiredLogMsgColor, ItemPurchaseResultString);
			FJLogUtility::PrintJLog(DesiredLogLevel, ItemPurchaseResultString);
		})
		);
	}
	);
}

bool UGameStoreItemObject::IsItemFocus()
{
	return bItemFocus;
}

void UGameStoreItemObject::EventExecute_Implementation()
{
	CreateItemPurchasePopup();
}

void UGameStoreItemObject::SetWidgetFocus_Implementation(bool bFoucs)
{
	bItemFocus = bFoucs;
}
