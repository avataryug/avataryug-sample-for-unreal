// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "AdsButton.h"
#include "AdsButtonsGrid.generated.h"

UCLASS()
class UAdsListData : public UObject {
	GENERATED_BODY()
public:
	int StartIndex;
	int TotalCount;
	 TArray<FAdsPlacementClass> rewardItem;
	FRewardItemClick callback;
	// UPROPERTY()
	// class UBundleDetailPanel *panel;
};
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UAdsButtonsGrid : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()
	
	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

protected:
	void NativeConstruct() override;

public:

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UAdsButton *AdsButton;

	UPROPERTY(EditAnywhere, meta = (BindWidget))
	UAdsButton *AdsButton_1;
	UPROPERTY()
	TArray<UAdsButton *> AdsButtonList;

};
