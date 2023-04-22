#pragma once

#include "CoreMinimal.h"

DECLARE_LOG_CATEGORY_EXTERN(JLog, Log, All);

UENUM(BlueprintType)
enum class EJLogLevel : uint8
{
	NONE = 0	UMETA(DisplayName = "None"),
	Fatal		UMETA(DisplayName = "Fatal"),
	Error		UMETA(DisplayName = "Error"), 
	Warning		UMETA(DisplayName = "Warning"), 
	Display		UMETA(DisplayName = "Display"),
};

/*
* 게임 프로젝트 사이드단 로그 일괄 핸들링을 위한 유틸리티 클래스
*/
class TESTPROJECT_API FJLogUtility
{
public:
	static void PrintJLog(EJLogLevel JLogLevel, const FString& LogMsg);
	static void PrintJScreenDebugLog(float ShowTime, FColor LogMsgColor, const FString& LogMsg); 
	
};
