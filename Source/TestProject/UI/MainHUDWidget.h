// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Type/JEnum.h"
#include "MainHUDWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UMainHUDWidget : public UUserWidget
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;
	virtual FReply NativeOnKeyDown(const FGeometry& InGeometry, const FKeyEvent& InKeyEvent) override;

public:
	UFUNCTION(BlueprintCallable)
		void Initalized();
	UFUNCTION(BlueprintCallable)
		void SetBackgroundColor(FLinearColor NewColor);
	UFUNCTION(BlueprintCallable)
		void SetStoreBackground(FLinearColor NewColor);
private:
	UFUNCTION()
		void OnLeftArrowButtonClicked();
	UFUNCTION()
		void OnRightArrowButtonClicked();
	UFUNCTION()
		void OnUpArrowButtonClicked();
	UFUNCTION()
		void OnDownArrowButtonClicked();

	void CreateAlertDialog(const FString& Contents);
	void OnFocusWidgetChanged(UObject* NewFocusWidget);

	UFUNCTION(BlueprintCallable)
		UWidget* DoGameStoreListViewNavigationRule(EUINavigation Direction);

public:
	FCustomWidgetNavigationDelegate OnGameStoreListViewNavigationCallback;

protected:
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)	
		class UBorder* Border_Background;
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UBorder* Border_StoreBackground;
	
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_LeftArrow;
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_RightArrow;
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_UpArrow;
	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UJButtonWidget* JBtn_DownArrow;

	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UTextBlock* Text_CurrentFocusWidget;

	UPROPERTY(Meta = (BindWidget), BlueprintReadOnly)
		class UGameStoreListView* JLV_GameStoreList;
	
};
