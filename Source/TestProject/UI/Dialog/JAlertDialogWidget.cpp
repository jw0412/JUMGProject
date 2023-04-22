#include "UI/Dialog/JAlertDialogWidget.h"

#include "UI/Button/JButton.h"
#include "UI/Button/JButtonWidget.h"

#include "Components/Border.h"
#include "Components/Spacer.h"
#include "Components/TextBlock.h"
#include "Components/CanvasPanelSlot.h"

#include "Manager/JWidgetManager.h"
#include "Utility/JLogUtility.h"

void UJAlertDialogWidget::NativePreConstruct()
{
	Super::NativePreConstruct();

	bIsFocusable = false;

	SetBackgroundColor(FLinearColor(0.f, 0.f, 0.f, 0.3f));
	SetDialogBackgroundColor(FLinearColor::White);
	SetTitleBackgroundColor(FLinearColor::White);
	SetButtonMargin(FVector2D(80.f, 70.f));
}

void UJAlertDialogWidget::NativeConstruct()
{
	Super::NativeConstruct();

	// Alert Dialog Ä¿½ºÅÒ ³×ºñ°ÔÀÌ¼Ç ·ê µî·Ï
	OnAlertDialogNavigationCallback.BindDynamic(this, &UJAlertDialogWidget::DoAlertDialogNavigationRule);
	JBtn_Cancle->SetNavigationRuleCustom(EUINavigation::Left, OnAlertDialogNavigationCallback);
	JBtn_Confirm->SetNavigationRuleCustom(EUINavigation::Right, OnAlertDialogNavigationCallback);

	JBtn_Confirm->OnButtonClicked().AddDynamic(this, &UJAlertDialogWidget::OnAlertDialogConfirm);
	JBtn_Cancle->OnButtonClicked().AddDynamic(this, &UJAlertDialogWidget::OnAlertDialogCancle);

	JBtn_Confirm->OnJButtonFocusEventExecute().AddDynamic(this, &UJAlertDialogWidget::OnAlertDialogConfirm);
	JBtn_Cancle->OnJButtonFocusEventExecute().AddDynamic(this, &UJAlertDialogWidget::OnAlertDialogCancle);
}

void UJAlertDialogWidget::NativeDestruct()
{
	Super::NativeDestruct();

	UnbindAlertDialogResultCallback();
	Owner = nullptr;
}

FReply UJAlertDialogWidget::NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent)
{
	if (InKeyEvent.GetKey() == EKeys::Enter)
	{
		JWIDGET_MGR().EventExecuteWithFocusWidget();
	}

	return FReply::Handled();
}

void UJAlertDialogWidget::InitalizeAlertDialog(UObject* OwningObject, const FString& Title, const FString& Contents, FVector2D DialogSize, FOnJDialogResult AlterDialogResultCallback)
{
	Owner = OwningObject;

	AsyncTask(ENamedThreads::GameThread, [=]
	{
		SetAlertDialogSize(DialogSize);
		Text_DialogTitle->SetText(FText::FromString(Title));
		Text_DialogContents->SetText(FText::FromString(Contents));

		// AlertDialog À§Á¬ÀÌ ´ÝÇûÀ»¶§ AlertDialog À§Á¬ÀÌ »ý¼ºµÇ±âÀü Æ÷Ä¿½ÌµÈ À§Á¬À¸·Î º¹±ÍÇÏ±â À§ÇÑ Æ÷Ä¿½Ì Á¤º¸ Ä³½Ì
		JWIDGET_MGR().SetPreviousFocusWidget();

		// AlertDialog À§Á¬ÀÌ »ý¼º‰çÀ»¶§ Confirm ¹öÆ°¿¡ ±âº» Æ÷Ä¿½ÌµÇµµ·Ï ¼³Á¤.
		JBtn_Confirm->JButtonFocusWidget();
		this->SetVisibility(ESlateVisibility::Visible);
	}
	);

	UnbindAlertDialogResultCallback();
	OnAlertDialogResultCallback = AlterDialogResultCallback;
}

void UJAlertDialogWidget::SetAlertDialogSize(FVector2D NewDialogSize)
{
	UCanvasPanelSlot* CanvasPanelSlot = Cast<UCanvasPanelSlot>(Border_Dialog->Slot);
	if (CanvasPanelSlot)
	{
		CanvasPanelSlot->SetSize(NewDialogSize);
	}
}

void UJAlertDialogWidget::SetBackgroundColor(FLinearColor NewColor)
{
	Border_Background->Background.TintColor = NewColor;
}

void UJAlertDialogWidget::SetDialogBackgroundColor(FLinearColor NewColor)
{
	Border_Dialog->Background.TintColor = NewColor;
}

void UJAlertDialogWidget::SetTitleBackgroundColor(FLinearColor NewColor)
{
	Border_TitleBackground->Background.TintColor = NewColor;
}

void UJAlertDialogWidget::SetButtonMargin(FVector2D NewMargin)
{
	Spacer_ButtonMargin->SetSize(NewMargin);
}

void UJAlertDialogWidget::UnbindAlertDialogResultCallback()
{
	if (OnAlertDialogResultCallback.IsBound())
	{
		OnAlertDialogResultCallback.Unbind();
	}
}

void UJAlertDialogWidget::OnAlertDialogConfirm()
{
	AsyncTask(ENamedThreads::GameThread, [=]
	{
		JWIDGET_MGR().SetFocusWidget(JWIDGET_MGR().GetPreviousFocusWidget());

		OnAlertDialogResultCallback.ExecuteIfBound(true);
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
	);
}

void UJAlertDialogWidget::OnAlertDialogCancle()
{
	AsyncTask(ENamedThreads::GameThread, [=]
	{
		JWIDGET_MGR().SetFocusWidget(JWIDGET_MGR().GetPreviousFocusWidget());

		OnAlertDialogResultCallback.ExecuteIfBound(false);
		this->SetVisibility(ESlateVisibility::Collapsed);
	}
	);
}

UWidget* UJAlertDialogWidget::DoAlertDialogNavigationRule(EUINavigation Direction)
{
	UWidget* ResultWidget = nullptr;
	switch (Direction)
	{
	case EUINavigation::Left:
	{
		ResultWidget = JBtn_Confirm;
		JBtn_Confirm->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("AlertDialogNavigationRule : Left"));
		break;
	}
	case EUINavigation::Right:
	{
		ResultWidget = JBtn_Cancle;
		JBtn_Cancle->JButtonFocusWidget();
		FJLogUtility::PrintJLog(EJLogLevel::Warning, TEXT("AlertDialogNavigationRule : Right"));
		break;
	}
	default:
		break;
	}

	return ResultWidget;
}
