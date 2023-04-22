// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Type/JEnum.h"
#include "GameFramework/PlayerController.h"
#include "JPlayerController.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AJPlayerController : public APlayerController
{
	GENERATED_BODY()
	
public:
	AJPlayerController();
	virtual void BeginPlay() override;

protected:
	virtual void SetupInputComponent() override;

private:
	void OnLeftArrowPressed();
	void OnRightArrowPressed();
	void OnUpArrowPressed();
	void OnDownArrowPressed();
	void OnEnterPressed();

};
