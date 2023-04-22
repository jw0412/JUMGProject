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
	// 위젯 포커싱 업데이트
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void SetWidgetFocus(bool bFoucs);

	// 포커싱되어있는 위젯 실행(액션) 이벤트
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void EventExecute();
};
