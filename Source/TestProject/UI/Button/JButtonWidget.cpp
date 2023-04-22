#include "UI/Button/JButtonWidget.h"

#include "Components/TextBlock.h"
#include "Components/Border.h"

#include "Utility/JLogUtility.h"
#include "Manager/JWidgetManager.h"

UJButtonWidget::UJButtonWidget(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bIsFocusable = false;
	DefaultButtonText = FString("Default Text");
}

void UJButtonWidget::NativePreConstruct()
{
	Super::NativePreConstruct();
	
	Border_FocusBox->SetVisibility(ESlateVisibility::Collapsed);
}

void UJButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();

	Btn_JB->OnHovered.AddDynamic(this, &UJButtonWidget::OnJButtonHovered);
	Btn_JB->OnJButtonFocuseChangedEvent.AddDynamic(this, &UJButtonWidget::OnJButtonWidgetFocusCallback);
}

void UJButtonWidget::NativeDestruct()
{
	Super::NativeDestruct();
}

void UJButtonWidget::SynchronizeProperties()
{
	Super::SynchronizeProperties();

	SetButtonText(DefaultButtonText);
}

void UJButtonWidget::OnJButtonHovered()
{
	this->SetKeyboardFocus();
	Btn_JB->JButtonFocusWidget();
}

void UJButtonWidget::OnJButtonWidgetFocusCallback(bool bFoucs)
{
	if (bFoucs)
	{
		this->SetKeyboardFocus();
	}

	Border_FocusBox->SetVisibility(bFoucs ? ESlateVisibility::HitTestInvisible : ESlateVisibility::Collapsed);
}

FString UJButtonWidget::GetButtonText()
{
	return DefaultButtonText;
}

void UJButtonWidget::SetButtonText(FString NewText)
{
	if (Text_Button != nullptr)
	{
		Text_Button->SetText(FText::FromString(NewText));
	}
}

class UButton* UJButtonWidget::GetJButton()
{
	return Btn_JB;
}

void UJButtonWidget::JButtonFocusWidget()
{
	OnJButtonHovered();
}

FOnButtonClickedEvent& UJButtonWidget::OnButtonClicked()
{
	return Btn_JB->OnClicked;
}

FOnJButtonFocuseChangedEvent& UJButtonWidget::OnJButtonFocuseChangedEvent()
{
	return Btn_JB->OnJButtonFocuseChangedEvent;
}

FOnJButtonFocusEventExecute& UJButtonWidget::OnJButtonFocusEventExecute()
{
	return Btn_JB->OnJButtonFocusEventExecute;
}

