// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/ListView.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "InventoryItemButton.generated.h"
DECLARE_DYNAMIC_DELEGATE_OneParam(FOnInventoryItemClick, FGetUserInventoryResultDataInner, data);
/**
 *
 */
UCLASS()
class UInvetoryItemListData : public UObject
{
	GENERATED_BODY()
public:
	FGetUserInventoryResultDataInner data;
	FOnInventoryItemClick callback;
};
UCLASS()
class AVATARYUGDEMO_API UInventoryItemButton : public UUserWidget, public IUserObjectListEntry
{
	GENERATED_BODY()

protected:
	void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

public:
	UPROPERTY(meta = (BindWidget))
	class UButton *ConsumeButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ItemName;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ItemID;

public:
	UFUNCTION()
	void OnClickConsumeButton();
	UPROPERTY()
	FOnInventoryItemClick InventoryItemClick;
	UPROPERTY()
	FGetUserInventoryResultDataInner item;
	UFUNCTION()
	void SetButtons(FOnInventoryItemClick callback, FGetUserInventoryResultDataInner _item);
};
