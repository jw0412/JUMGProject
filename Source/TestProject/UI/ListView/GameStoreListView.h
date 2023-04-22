// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UI/ListView/JListView.h"
#include "GameStoreListView.generated.h"

/**
 * 
 */
UCLASS()
class TESTPROJECT_API UGameStoreListView : public UJListView
{
	GENERATED_BODY()
	
public:
	UGameStoreListView(const FObjectInitializer& Initializer);



protected:
	virtual void OnItemClickedInternal(UObject* Item) override;
	virtual void OnItemDoubleClickedInternal(UObject* Item) override;
	virtual void OnSelectionChangedInternal(UObject* FirstSelectedItem) override;
	virtual void OnItemScrolledIntoViewInternal(UObject* Item, UUserWidget& EntryWidget) override;
	virtual void HandleListEntryHovered(UUserWidget& EntryWidget) override;
public:
	void AddGameStoreItems();
	void RefreshGameStoreList();
private:
	void OnGameSotreListItemHovered(UObject* HoveredItem, bool bIsHovered);
	void OnFocusWidgetChanged(UObject* NewFocusWidget);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStore ListView Setup")
		TArray<FString> StoreItemNames;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "GameStore ListView Setup")
		int32 CreateStoreItemNum;

};
