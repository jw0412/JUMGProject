#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "JGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UJGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;
	virtual void Shutdown() override;

};
