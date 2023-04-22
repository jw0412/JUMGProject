#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "WidgetFocusInterface.generated.h"

UINTERFACE(MinimalAPI)
class UWidgetFocusInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class TESTPROJECT_API IWidgetFocusInterface
{
	GENERATED_BODY()

public:
	// ���� ��Ŀ�� ������Ʈ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetWidgetFocus(bool bFoucs);

	// ��Ŀ�̵Ǿ��ִ� ���� ����(�׼�) �̺�Ʈ
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EventExecute();
};
