#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/JDelegate.h"
#include "Type/JEnum.h"
#include "JAlertDialogWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UJAlertDialogWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown( const FGeometry& InGeometry, const FKeyEvent& InKeyEvent ) override;

public:
	void InitalizeAlertDialog(UObject* OwningObject, const FString& Title, const FString& Contents, FVector2D DialogSize = FVector2D(1000.f, 750.f), FOnJDialogResult AlterDialogResultCallback = NULL);
	void SetAlertDialogSize(FVector2D newDialogSize);

	UFUNCTION(BlueprintCallable)
		void SetBackgroundColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
		void SetDialogBackgroundColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
		void SetTitleBackgroundColor(FLinearColor NewColor);

	UFUNCTION(BlueprintCallable)
		void SetButtonMargin(FVector2D NewMargin);

	UFUNCTION(BlueprintCallable)
		void UnbindAlertDialogResultCallback();

private:
	UFUNCTION(BlueprintCallable)
		void OnAlertDialogConfirm();
	UFUNCTION(BlueprintCallable)
		void OnAlertDialogCancle();

	UFUNCTION(BlueprintCallable)
		UWidget* DoAlertDialogNavigationRule(EUINavigation Direction);

public:
	FCustomWidgetNavigationDelegate OnAlertDialogNavigationCallback;

protected:
	UPROPERTY(Meta = (BindWidget))
		class UBorder* Border_Background;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* Border_TitleBackground;
	UPROPERTY(Meta = (BindWidget))
		class UBorder* Border_Dialog;

	UPROPERTY(Meta = (BindWidget))	
		class UTextBlock* Text_DialogTitle;
	UPROPERTY(Meta = (BindWidget))	
		class UTextBlock* Text_DialogContents;

	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_Confirm;
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_Cancle;

	UPROPERTY(Meta = (BindWidget))
		class USpacer* Spacer_ButtonMargin;

	UObject* Owner;

private:
	FOnJDialogResult OnAlertDialogResultCallback;

};
