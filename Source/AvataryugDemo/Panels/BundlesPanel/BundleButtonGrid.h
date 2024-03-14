// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "BundlesData.h"
#include "BundleButton.h"
#include "BundleDetailPanel.h"
#include "BundleButtonGrid.generated.h"

UCLASS()
class UBundleListData : public UObject {
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	TArray<FEconomyBundle> bundleItem;
	UPROPERTY()
	class UBundleDetailPanel *panel;
};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBundleButtonGrid : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

protected:
	void NativeConstruct() override;
public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBundleButton *WBP_BundlesItemButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UBundleButton *WBP_BundlesItemButton_1;

	TArray<UBundleButton *> BundlesButtonList;
};
