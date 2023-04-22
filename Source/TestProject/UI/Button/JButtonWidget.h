#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "UI/Button/JButton.h"
#include "Type/JDelegate.h"
#include "JButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UJButtonWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	UJButtonWidget(const FObjectInitializer& ObjectInitializer);

	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual void SynchronizeProperties() override;

public:
	UFUNCTION(BlueprintPure)
		FString GetButtonText();

	UFUNCTION(BlueprintCallable)
		void SetButtonText(FString NewText);

	UFUNCTION(BlueprintPure)
		class UButton* GetJButton();

	UFUNCTION(BlueprintCallable)
		void JButtonFocusWidget();


	FOnButtonClickedEvent& OnButtonClicked();
	FOnJButtonFocuseChangedEvent& OnJButtonFocuseChangedEvent();
	FOnJButtonFocusEventExecute& OnJButtonFocusEventExecute();

protected:
	UFUNCTION(BlueprintCallable)
		void OnJButtonHovered();
	UFUNCTION(BlueprintCallable)
		void OnJButtonWidgetFocusCallback(bool bFoucs);

protected:

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "JButton Setup")
		FString DefaultButtonText;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Text_Button;

	UPROPERTY(Meta = (BindWidget))
		class UJButton* Btn_JB;

	UPROPERTY(Meta = (BindWidget))
		class UBorder* Border_FocusBox;
};
