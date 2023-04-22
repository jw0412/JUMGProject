#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "GameStoreItemWidget.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGameStoreItemWidget : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
protected:
	virtual void NativePreConstruct() override;
	virtual void NativeConstruct() override;
	virtual void NativeDestruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

private:
	void OnStoreItemFocuseChangedCallback(bool bFocus);

private:
	UPROPERTY(Meta = (BindWidget))
		class UImage* Img_Item;

	UPROPERTY(Meta = (BindWidget))
		class UTextBlock* Text_ItemName;

	UPROPERTY(Meta = (BindWidget))
		class UBorder* Border_FocusBox;
};
