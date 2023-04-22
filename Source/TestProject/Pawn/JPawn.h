#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "JPawn.generated.h"

UCLASS()
class TESTPROJECT_API AJPawn : public APawn
{
	GENERATED_BODY()

public:
	AJPawn();

protected:
	virtual void BeginPlay() override;

public:	
	virtual void Tick(float DeltaTime) override;
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

};
