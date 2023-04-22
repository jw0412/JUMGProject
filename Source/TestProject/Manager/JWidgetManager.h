#pragma once

#include "CoreMinimal.h"
#include "Design/SingleTon/JSingleTon.h"
#include "GameFramework/PlayerController.h"
#include "Components/Widget.h"
#include "Type/JDelegate.h"

/*
* 위젯 생성과 포커싱을 일괄 핸들링하기 위한 매니저 클래스
*/
#define JWIDGET_MGR() FJWidgetManager::GetInstance()
class TESTPROJECT_API FJWidgetManager : public FJSingleTon<FJWidgetManager>
{
public:
	const FSoftClassPath MainHUDWidgetFilePath = TEXT("/Game/Blueprints/UI/WBP_MainHUD.WBP_MainHUD_C");
	const FSoftClassPath AlertDialogWidgetFilePath = TEXT("/Game/Blueprints/UI/Dialog/WBP_AlertDialog.WBP_AlertDialog_C");
	const FSoftClassPath GameStoreItemWidgetFilePath = TEXT("/Game/Blueprints/UI/GameStore/WBP_GameStoreItem.WBP_GameStoreItem_C");

public:
	FJWidgetManager();
	~FJWidgetManager();

public:
	// create widget
	class UMainHUDWidget* CreateMainHUDWidget(UObject* OwningObject);
	class UJAlertDialogWidget* CreateAlertDialogWidget(UObject* OwningObject, FString Title, FString Contents, FVector2D DialogSize = FVector2D(800.f, 450.f), FOnJDialogResult AlterDialogResultCallback = NULL);
	class UJAlertDialogWidget* GetAlertDialogWidget();
	class UMainHUDWidget* GetMainHUDWidget();

	// widget focus
	UObject* GetCurrentFocusWidget();
	UObject* GetPreviousFocusWidget();
	void SetPreviousFocusWidget();
	void SetFocusWidget(UObject* NewFocusWidget);
	void EventExecuteWithFocusWidget();
	void AddFocusWidgetChangedListener(FOnFocusWidgetChanged::FDelegate FocusWidgetChangedCallback);

protected:
	FOnFocusWidgetChanged OnFocusWidgetChanged;

protected:

	UPROPERTY()
		class UJAlertDialogWidget* AlertDialog = nullptr;
	UPROPERTY()
		class UMainHUDWidget* MainHUDWidget = nullptr;

	UPROPERTY()
		UObject* CurrentFocusWidget = nullptr;
	UPROPERTY()
		UObject* PreviousFocusWidget= nullptr;

private:
	float DelaySetKeyBoardFocusInterval = 0.04f;

};
