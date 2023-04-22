#include "JPlayerController.h"
#include "Utility/JLogUtility.h"
#include "Manager/JWidgetManager.h"

AJPlayerController::AJPlayerController()
{
	bShowMouseCursor = true;
}

void AJPlayerController::BeginPlay()
{
	Super::BeginPlay();

	//SetIgnoreLookInput(true);
	//SetIgnoreMoveInput(true);
	SetInputMode(FInputModeGameAndUI());
}

void AJPlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	check(InputComponent);

	InputComponent->BindAction("LeftArrow", IE_Pressed, this, &AJPlayerController::OnLeftArrowPressed);
	InputComponent->BindAction("RightArrow", IE_Pressed, this, &AJPlayerController::OnRightArrowPressed);
	InputComponent->BindAction("UpArrow", IE_Pressed, this, &AJPlayerController::OnUpArrowPressed);
	InputComponent->BindAction("DownArrow", IE_Pressed, this, &AJPlayerController::OnDownArrowPressed);

	InputComponent->BindAction("Enter", IE_Pressed, this, &AJPlayerController::OnEnterPressed);
}

void AJPlayerController::OnLeftArrowPressed()
{
// 	const FString DesiredLogMsg = FString::Printf(TEXT("[%s] 왼쪽 방향키를 누르셨습니다."), *this->GetName());
// 	FJLogUtility::PrintJLog(EJLogLevel::Display, DesiredLogMsg);
}

void AJPlayerController::OnRightArrowPressed()
{
// 	const FString DesiredLogMsg = FString::Printf(TEXT("[%s] 오른쪽 방향키를 누르셨습니다."), *this->GetName());
// 	FJLogUtility::PrintJLog(EJLogLevel::Display, DesiredLogMsg);
}

void AJPlayerController::OnUpArrowPressed()
{
// 	const FString DesiredLogMsg = FString::Printf(TEXT("[%s] 위 방향키를 누르셨습니다."), *this->GetName());
// 	FJLogUtility::PrintJLog(EJLogLevel::Display, DesiredLogMsg);
}

void AJPlayerController::OnDownArrowPressed()
{
// 	const FString DesiredLogMsg = FString::Printf(TEXT("[%s] 아래 방향키를 누르셨습니다."), *this->GetName());
// 	FJLogUtility::PrintJLog(EJLogLevel::Display, DesiredLogMsg);
}

void AJPlayerController::OnEnterPressed()
{
// 	const FString DesiredLogMsg = FString::Printf(TEXT("[%s] 엔터 키를 누르셨습니다."), *this->GetName());
// 	FJLogUtility::PrintJLog(EJLogLevel::Display, DesiredLogMsg);
}
