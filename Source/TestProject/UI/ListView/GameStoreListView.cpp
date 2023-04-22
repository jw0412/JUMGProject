#include "UI/ListView/GameStoreListView.h"
#include "UI/GameStore/GameStoreItemObject.h"

#include "Manager/JWidgetManager.h"

UGameStoreListView::UGameStoreListView(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	EntryWidgetClass = JWIDGET_MGR().GameStoreItemWidgetFilePath.TryLoadClass<class UUserWidget>();

	StoreItemNames = {
						   TEXT("회복용 물약"),
						   TEXT("보조용 물약"),
						   TEXT("장비 강화 주문서"),
						   TEXT("이동 주문서"),
						   TEXT("장비 강화 주문서"),
						   TEXT("일반 주문서"),
						   TEXT("시간 충전석"),
						   TEXT("숨겨진 마족의 검"),
						   TEXT("신묘한 장검"),
						   TEXT("영웅의 한손검"),
						   TEXT("커츠의 검"),
						   TEXT("데스나이트 불검"),
						   TEXT("포르세의 검"),
						   TEXT("고대 다크엘프의 검"),
						   TEXT("고대의 검"),
						   TEXT("단검신"),
						   TEXT("그라디우스"),
						   TEXT("넓은 검"),
						   TEXT("난쟁이족 검"),
						   TEXT("진 레이피어")
					 };

	CreateStoreItemNum = 300;

	OnItemIsHoveredChanged().AddUObject(this, &UGameStoreListView::OnGameSotreListItemHovered);

	// Focus Widget Changed Event
	JWIDGET_MGR().AddFocusWidgetChangedListener(FOnFocusWidgetChanged::FDelegate::CreateUObject(this, &UGameStoreListView::OnFocusWidgetChanged));
}

void UGameStoreListView::AddGameStoreItems()
{
	for (int32 index = 0; index < CreateStoreItemNum; index++)
	{
		FString DesiredItemName = TEXT("알 수 없는 아이템");
		if (StoreItemNames.Num() > 0)
		{
			const int32 RandomNumber = FMath::RandRange(0, StoreItemNames.Num() - 1);
			DesiredItemName = StoreItemNames[RandomNumber];
		}

		UGameStoreItemObject* StoreItemObj = NewObject<UGameStoreItemObject>();
		StoreItemObj->SetData(this, DesiredItemName, false);

		this->AddItem(StoreItemObj);
	}
}

void UGameStoreListView::RefreshGameStoreList()
{
	this->RegenerateAllEntries();
}

void UGameStoreListView::OnItemClickedInternal(UObject* Item)
{
	Super::OnItemClickedInternal(Item);

	UGameStoreItemObject* StoreItemObj = Cast<UGameStoreItemObject>(Item);
	if (StoreItemObj)
	{
		StoreItemObj->CreateItemPurchasePopup();
	}
}

void UGameStoreListView::OnItemDoubleClickedInternal(UObject* Item)
{
	Super::OnItemDoubleClickedInternal(Item);
}

void UGameStoreListView::OnSelectionChangedInternal(UObject* FirstSelectedItem)
{
	Super::OnSelectionChangedInternal(FirstSelectedItem);
}

void UGameStoreListView::OnItemScrolledIntoViewInternal(UObject* Item, UUserWidget& EntryWidget)
{
	Super::OnItemScrolledIntoViewInternal(Item, EntryWidget);

	JWIDGET_MGR().SetFocusWidget(Item);
	EntryWidget.SetKeyboardFocus();
}

void UGameStoreListView::HandleListEntryHovered(UUserWidget& EntryWidget)
{
	Super::HandleListEntryHovered(EntryWidget);
	EntryWidget.SetKeyboardFocus();
}

void UGameStoreListView::OnGameSotreListItemHovered(UObject* HoveredItem, bool bIsHovered)
{
	if (bIsHovered)
	{
		JWIDGET_MGR().SetFocusWidget(HoveredItem);
	}
}

void UGameStoreListView::OnFocusWidgetChanged(UObject* NewFocusWidget)
{
	// 리스트 뷰 아이템 오브젝트의 포커스 정보가 업데이트되면 리스트 뷰 위젯 리프레시.
	RefreshGameStoreList();
}