#include "UI/Button/JButton.h"
#include "Components/ButtonSlot.h"
#include "Manager/JWidgetManager.h"

UJButton::UJButton(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	ClickMethod = EButtonClickMethod::PreciseClick;
	TouchMethod = EButtonTouchMethod::PreciseTap;
	PressMethod = EButtonPressMethod::DownAndUp;
}

void UJButton::JButtonFocusWidget()
{
	JWIDGET_MGR().SetFocusWidget(this);
}

TSharedRef<SWidget> UJButton::RebuildWidget()
{
	// 버튼 이벤트들을 JButton 클래스 핸들링 하기 위한 RebuildWidget
	MyButton = SNew(SButton)
		.OnClicked(BIND_UOBJECT_DELEGATE(FOnClicked, SlateHandleJClicked))
		.OnPressed(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleJPressed))
		.OnReleased(BIND_UOBJECT_DELEGATE(FSimpleDelegate, SlateHandleJReleased))
		.OnHovered_UObject(this, &ThisClass::SlateHandleJHovered)
		.OnUnhovered_UObject(this, &ThisClass::SlateHandleJUnhovered)
		.ButtonStyle(&WidgetStyle)
		.ClickMethod(ClickMethod)
		.TouchMethod(TouchMethod)
		.PressMethod(PressMethod)
		.IsFocusable(IsFocusable)
		;

	if (GetChildrenCount() > 0)
	{
		Cast<UButtonSlot>(GetContentSlot())->BuildSlot(MyButton.ToSharedRef());
	}

	return MyButton.ToSharedRef();
}

FReply UJButton::SlateHandleJClicked()
{
	OnClicked.Broadcast();
	return FReply::Handled();
}

void UJButton::SlateHandleJPressed()
{
	OnPressed.Broadcast();
}

void UJButton::SlateHandleJReleased()
{
	OnReleased.Broadcast();
}

void UJButton::SlateHandleJHovered()
{
	//JButtonFocusWidget();
	OnHovered.Broadcast();
}

void UJButton::SlateHandleJUnhovered()
{
	OnUnhovered.Broadcast();
}

void UJButton::EventExecute_Implementation()
{
	OnJButtonFocusEventExecute.Broadcast();
}

void UJButton::SetWidgetFocus_Implementation(bool bFoucs)
{
	OnJButtonFocuseChangedEvent.Broadcast(bFoucs);
}
