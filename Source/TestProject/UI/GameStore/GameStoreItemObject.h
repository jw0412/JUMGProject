#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "Design/Interface/WidgetFocusInterface.h"
#include "GameStoreItemObject.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGameStoreItemObject : public UObject, public IWidgetFocusInterface
{
	GENERATED_BODY()
	
public:
	void SetData(UObject* NewOwningWidget, const FString& NewItemName, bool bNewItemFocus);
	FString GetItemName();
	void CreateItemPurchasePopup();

	bool IsItemFocus();


	virtual void SetWidgetFocus_Implementation(bool bFoucs) override;
	virtual void EventExecute_Implementation() override;

protected:
	UPROPERTY()
		FString ItemName;

	UPROPERTY()
		UObject* OwningWidget;

	UPROPERTY()
		bool bItemFocus = false;
};
