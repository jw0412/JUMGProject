// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "JHUD.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API AJHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	void BeginPlay() override;
	void Destroyed() override;
	
};
