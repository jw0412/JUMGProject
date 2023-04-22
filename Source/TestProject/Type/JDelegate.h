#pragma once
#include "CoreMinimal.h"

DECLARE_DELEGATE_OneParam(FOnJDialogResult, bool) // 다이얼로그 컨펌 여부 콜백
DECLARE_MULTICAST_DELEGATE_OneParam(FOnFocusWidgetChanged, UObject*) // 위젯 포커스 변경 알림

