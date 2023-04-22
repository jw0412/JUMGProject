#include "JWidgetManager.h"
#include "UI/MainHUDWidget.h"
#include "UI/Dialog/JAlertDialogWidget.h"
#include "Utility/JLogUtility.h"
#include "Design/Interface/WidgetFocusInterface.h"

FJWidgetManager::FJWidgetManager()
{

}

FJWidgetManager::~FJWidgetManager()
{
	if (AlertDialog)
	{
		AlertDialog->RemoveFromParent();
	}
	if (MainHUDWidget)
	{
		MainHUDWidget->RemoveFromParent();
	}
}

class UMainHUDWidget* FJWidgetManager::CreateMainHUDWidget(UObject* OwningObject)
{
	if (OwningObject)
	{
		UWorld* World = OwningObject->GetWorld();
		if (World)
		{
			if (MainHUDWidget)
			{
				MainHUDWidget->Initalized();
			}
			else
			{
				// MainHUD UMG ����
				TSubclassOf<class UMainHUDWidget> MainHUDWidgetClass = MainHUDWidgetFilePath.TryLoadClass<class UUserWidget>();
				if (MainHUDWidgetClass != NULL)
				{
					MainHUDWidget = CreateWidget<UMainHUDWidget>(World, MainHUDWidgetClass);
					if (MainHUDWidget)
					{
						MainHUDWidget->Initalized();
						MainHUDWidget->AddToViewport(10);
						return MainHUDWidget;
					}
				}
			}
		}
		else
		{
			FJLogUtility::PrintJLog(EJLogLevel::Error, "[FJWidgetManager] Create MainHUD Widget Failed : World Obj Nullptr.");
		}
	}
	else
	{
		FJLogUtility::PrintJLog(EJLogLevel::Error, "[FJWidgetManager]Create MainHUD Widget Failed.");
	}

	return nullptr;
}

class UJAlertDialogWidget* FJWidgetManager::CreateAlertDialogWidget(UObject* OwningObject, FString Title, FString Contents, FVector2D DialogSize, FOnJDialogResult AlterDialogResultCallback)
{
	if (OwningObject)
	{
		UWorld* World = OwningObject->GetWorld();
		if (World)
		{
			if (AlertDialog)
			{
				AlertDialog->InitalizeAlertDialog(OwningObject, Title, Contents, DialogSize, AlterDialogResultCallback);
			}
			else
			{
				// Alert Dialog UMG ����
				TSubclassOf<class UJAlertDialogWidget> AlertDialogWidgetClass = AlertDialogWidgetFilePath.TryLoadClass<class UUserWidget>();
				if (AlertDialogWidgetClass != NULL)
				{
					AlertDialog = CreateWidget<UJAlertDialogWidget>(World, AlertDialogWidgetClass);
					if (AlertDialog)
					{
						AlertDialog->InitalizeAlertDialog(OwningObject, Title, Contents, DialogSize, AlterDialogResultCallback);
						AlertDialog->AddToViewport(10);
						return AlertDialog;
					}
				}
			}

		}
		else
		{
			FJLogUtility::PrintJLog(EJLogLevel::Error, "[FJWidgetManager] Create AlertDialog Widget Failed : World Obj Nullptr.");
		}
	}
	else
	{
		FJLogUtility::PrintJLog(EJLogLevel::Error, "[FJWidgetManager]Create AlertDialog Widget Failed.");
	}

	return nullptr;
}

UObject* FJWidgetManager::GetCurrentFocusWidget()
{
	return CurrentFocusWidget;
}

UObject* FJWidgetManager::GetPreviousFocusWidget()
{
	return PreviousFocusWidget;
}

void FJWidgetManager::SetPreviousFocusWidget()
{
	// AlertDialog ������ ���� ������ �ݰ��� ���� ��Ŀ�̵� �������� ������ ���� �������� ���� ��Ŀ�̵� ������ ĳ��.
	PreviousFocusWidget = CurrentFocusWidget;
}

void FJWidgetManager::SetFocusWidget(UObject* NewFocusWidget)
{
	// ��Ŀ���� ������ NULL�̰ų� ���� ��Ŀ���� ������ ������ ��� �ٷ� ����.
	if (NewFocusWidget == nullptr || CurrentFocusWidget == NewFocusWidget)
	{
		//FJLogUtility::PrintJLog(EJLogLevel::Warning, "[FJWidgetManager] SetFocusWidget : NewFocusWidget nullptr or When CurrentFocusWidget and NewFocusWidget are the same.");
		return;
	}

	IWidgetFocusInterface* WidgetFocusInterface = Cast<IWidgetFocusInterface>(NewFocusWidget);
	if (WidgetFocusInterface)
	{
		if (CurrentFocusWidget)
		{
			// ���� ��Ŀ���� ������ ������ ���� ��Ŀ���� ������ ��Ŀ�� ��Ȱ��ȭ.
			IWidgetFocusInterface* CurrentWidgetFocusInterface = Cast<IWidgetFocusInterface>(CurrentFocusWidget);
			CurrentWidgetFocusInterface->Execute_SetWidgetFocus(CurrentFocusWidget, false);
		}

		CurrentFocusWidget = NewFocusWidget;
		WidgetFocusInterface->Execute_SetWidgetFocus(NewFocusWidget, true);

		// ������Ʈ�� ��Ŀ�� ���� ������ �˸�. 
		OnFocusWidgetChanged.Broadcast(NewFocusWidget);
	}
	else
	{
		const FString DesiredLogMsg = FString::Printf(TEXT("[FJWidgetManager] SetFocusWidget : Focus Impossible Widget : %s"), *NewFocusWidget->GetName());
		FJLogUtility::PrintJLog(EJLogLevel::Warning, DesiredLogMsg);
	}
}

void FJWidgetManager::EventExecuteWithFocusWidget()
{
	if (CurrentFocusWidget)
	{
		IWidgetFocusInterface* CurrentWidgetFocusInterface = Cast<IWidgetFocusInterface>(CurrentFocusWidget);
		CurrentWidgetFocusInterface->Execute_EventExecute(CurrentFocusWidget);
	}
}

void FJWidgetManager::AddFocusWidgetChangedListener(FOnFocusWidgetChanged::FDelegate FocusWidgetChangedCallback)
{
	OnFocusWidgetChanged.Add(FocusWidgetChangedCallback);
}

class UJAlertDialogWidget* FJWidgetManager::GetAlertDialogWidget()
{
	return AlertDialog;
}

class UMainHUDWidget* FJWidgetManager::GetMainHUDWidget()
{
	return MainHUDWidget;
}
