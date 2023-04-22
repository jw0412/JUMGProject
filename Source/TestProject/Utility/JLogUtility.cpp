#include "JLogUtility.h"

DEFINE_LOG_CATEGORY(JLog);

static uint64 ScreenDebugLogKey = 0;

void FJLogUtility::PrintJLog(EJLogLevel JLogLevel, const FString& LogMsg)
{
	switch (JLogLevel)
	{
	case EJLogLevel::Warning:
		UE_LOG(JLog, Warning, TEXT("%s"), *LogMsg);
		break;
	case EJLogLevel::Fatal:
		UE_LOG(JLog, Fatal, TEXT("%s"), *LogMsg);
		break;
	case EJLogLevel::Error:
		UE_LOG(JLog, Error, TEXT("%s"), *LogMsg);
		break;
	default:
		UE_LOG(JLog, Display, TEXT("%s"), *LogMsg);
		break;
	}
}

void FJLogUtility::PrintJScreenDebugLog(float ShowTime, FColor LogMsgColor, const FString& LogMsg)
{
	GEngine->AddOnScreenDebugMessage(ScreenDebugLogKey, ShowTime, LogMsgColor, LogMsg);
	ScreenDebugLogKey++;
}
