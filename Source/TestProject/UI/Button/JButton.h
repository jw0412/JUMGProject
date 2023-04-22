#pragma once

#include "CoreMinimal.h"
#include "Components/Button.h"
#include "Design/Interface/WidgetFocusInterface.h"
#include "JButton.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnJButtonFocuseChangedEvent, bool, bFocus);
DECLARE_DYNAMIC_MULTICAST_DELEGATE(FOnJButtonFocusEventExecute);
/**
 *
 */
UCLASS()
class TESTPROJECT_API UJButton : public UButton, public IWidgetFocusInterface
{
	GENERATED_BODY()

public:
	UJButton(const FObjectInitializer& ObjectInitializer);

	virtual void SetWidgetFocus_Implementation(bool bFoucs) override;
	virtual void EventExecute_Implementation() override;
	void JButtonFocusWidget();

protected:
	//~ Begin UWidget Interface
	virtual TSharedRef<SWidget> RebuildWidget() override;

	FReply SlateHandleJClicked();
	void SlateHandleJPressed();
	void SlateHandleJReleased();
	void SlateHandleJHovered();
	void SlateHandleJUnhovered();

public:
	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On JButton Focuse Changed"))
		FOnJButtonFocuseChangedEvent OnJButtonFocuseChangedEvent;

	UPROPERTY(BlueprintAssignable, Category = Events, meta = (DisplayName = "On JButton Focus Event Execute"))
		FOnJButtonFocusEventExecute OnJButtonFocusEventExecute;
};
