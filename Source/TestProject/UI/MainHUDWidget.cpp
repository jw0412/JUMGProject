#include "MainHUDWidget.h"

#include "Components/Border.h"
#include "Components/TextBlock.h"
#include "Components/ListView.h"

#include "UI/Button/JButtonWidget.h"
#include "UI/ListView/GameStoreListView.h"

#include "Manager/JWidgetManager.h"

#include "Utility/JLogUtility.h"

void UMainHUDWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = false;
	SetBackgroundColor(FLinearColor::White);
	SetStoreBackground(FLinearColor(0.242281f, 0.07036f, 0.004777f, 1.f));
}

void UMainHUDWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// 게임 상점리스트 커스텀 네비게이션 룰 등록
	OnGameStoreListViewNavigationCallback.BindDynamic(this, &UMainHUDWidget::DoGameStoreListViewNavigationRule);
	JLV_GameStoreList->SetNavigationRuleCustom(EUINavigation::Up, OnGameStoreListViewNavigationCallback);
	JLV_GameStoreList->SetNavigationRuleCustom(EUINavigation::Down, OnGameStoreListViewNavigationCallback);
	JLV_GameStoreList->SetNavigationRuleCustom(EUINavigation::Left, OnGameStoreListViewNavigationCallback);
	JLV_GameStoreList->SetNavigationRuleCustom(EUINavigation::Right, OnGameStoreListViewNavigationCallback);

	// Button Click Events
	JBtn_LeftArrow->OnButtonClicked().AddDynamic(this, &UMainHUDWidget::OnLeftArrowButtonClicked);
	JBtn_RightArrow->OnButtonClicked().AddDynamic(this, &UMainHUDWidget::OnRightArrowButtonClicked);
	JBtn_UpArrow->OnButtonClicked().AddDynamic(this, &UMainHUDWidget::OnUpArrowButtonClicked);
	JBtn_DownArrow->OnButtonClicked().AddDynamic(this, &UMainHUDWidget::OnDownArrowButtonClicked);

	// Widget Fouce Execute Events
	JBtn_LeftArrow->OnJButtonFocusEventExecute().AddDynamic(this, &UMainHUDWidget::OnLeftArrowButtonClicked);
	JBtn_RightArrow->OnJButtonFocusEventExecute().AddDynamic(this, &UMainHUDWidget::OnRightArrowButtonClicked);
	JBtn_UpArrow->OnJButtonFocusEventExecute().AddDynamic(this, &UMainHUDWidget::OnUpArrowButtonClicked);
	JBtn_DownArrow->OnJButtonFocusEventExecute().AddDynamic(this, &UMainHUDWidget::OnDownArrowButtonClicked);

	// 게임 상점리스트에 기본 아이템 등록
	JLV_GameStoreList->AddGameStoreItems();

	// Focus Widget Changed Event
	JWIDGET_MGR().AddFocusWidgetChangedListener(FOnFocusWidgetChanged::FDelegate::CreateUObject(this, &UMainHUDWidget::OnFocusWidgetChanged));

	// MainHUD 위젯이 생성됬을때 UpArrow 버튼에 기본으로 포커싱이 되도록 설정
	JBtn_UpArrow->JButtonFocusWidget();
}

void UMainHUDWidget::NativeDestruct()
{
	Super::NativeDestruct();

}

FReply UMainHUDWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		JWIDGET_MGR().EventExecuteWithFocusWidget();
	}

	return FReply::Handled();
}

void UMainHUDWidget::Initalized()
{
	this->SetVisibility(ESlateVisibility::Visible);
}

void UMainHUDWidget::SetBackgroundColor(FLinearColor NewColor)
{
	Border_Background->Background.TintColor = NewColor;
}

void UMainHUDWidget::SetStoreBackground(FLinearColor NewColor)
{
	Border_StoreBackground->Background.TintColor = NewColor;
}

void UMainHUDWidget::OnLeftArrowButtonClicked()
{
	CreateAlertDialog(TEXT("왼쪽 방향키 버튼을 클릭하셨습니다."));
}

void UMainHUDWidget::OnRightArrowButtonClicked()
{
	CreateAlertDialog(TEXT("오른쪽 방향키 버튼을 클릭하셨습니다."));
}

void UMainHUDWidget::OnUpArrowButtonClicked()
{
	CreateAlertDialog(TEXT("위 방향키 버튼을 클릭하셨습니다."));
}

void UMainHUDWidget::OnDownArrowButtonClicked()
{
	CreateAlertDialog(TEXT("아래 방향키 버튼을 클릭하셨습니다."));
}

void UMainHUDWidget::CreateAlertDialog(const FString& Contents)
{
	AsyncTask(ENamedThreads::GameThread, [=]
	{
		JWIDGET_MGR().CreateAlertDialogWidget(this, TEXT("JDialog"), Contents, FVector2D(800.f, 450.f), FOnJDialogResult::CreateLambda([=](bool bConfirm)
		{
			const FString DesiredLogMsg = FString::Printf(TEXT("[%s] Jaewon Alert Dialog : [Confirm : %d]"), *this->GetName(), bConfirm);
			FJLogUtility::PrintJLog(EJLogLevel::Warning, DesiredLogMsg);
		})
		);
	}
	);
}

void UMainHUDWidget::OnFocusWidgetChanged(UObject* NewFocusWidget)
{
	// 현재 포커싱된 위젯 디버깅을 위한 텍스트 위젯 업데이트
	const FString DesiredFocusObjName = FString::Printf(TEXT("%s [UID : %d]"), *NewFocusWidget->GetName(), NewFocusWidget->GetUniqueID());
	const FString CurrentFocusWidgetText = FString::Printf(TEXT("Current Focus Widget : %s"), *DesiredFocusObjName);
	Text_CurrentFocusWidget->SetText(FText::FromString(CurrentFocusWidgetText));
}

UWidget* UMainHUDWidget::DoGameStoreListViewNavigationRule(EUINavigation Direction)
{
	UWidget* ReturnWidget = nullptr;

	switch (Direction)
	{
	case EUINavigation::Left:
	{
		ReturnWidget = JBtn_LeftArrow;
		JBtn_LeftArrow->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("GameStoreListViewNavigationRule : Left"));
		break;
	}
	case EUINavigation::Right:
	{
		ReturnWidget = JBtn_RightArrow;
		JBtn_RightArrow->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("GameStoreListViewNavigationRule : Right"));
		break;
	}
	case EUINavigation::Up:
	{
		ReturnWidget = JBtn_UpArrow;
		JBtn_UpArrow->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("GameStoreListViewNavigationRule : Up"));
		break;
	}
	case EUINavigation::Down:
	{
		ReturnWidget = JBtn_DownArrow;
		JBtn_DownArrow->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("GameStoreListViewNavigationRule : Down"));
		break;
	}
	default:
		break;
	}

	return ReturnWidget;
}
