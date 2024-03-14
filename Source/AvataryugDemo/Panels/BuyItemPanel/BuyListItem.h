// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "../../DataHolders/EconomyItemHolder.h"
#include "../../DataHolders/AllGraphicsHolder.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Image.h"
#include "../../DataHolders/CommonFunction.h"
#include "../../Utilitys/LoadTextureFromURL.h"
#include "BuyListItem.generated.h"

UCLASS()
class UBuyItemListData : public UObject {
	GENERATED_BODY()
public:
  int Index;
  FEconomyItems EconomyItem;
};

/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UBuyListItem : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()
	protected:
  void NativeConstruct() override;

    UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Avataryug")
    AAllGraphicsHolder *AllGraphicsHolder;

	virtual void NativeOnListItemObjectSet(UObject *ListItemObject) override;

	UPROPERTY(meta = (BindWidget))
	class UImage *ItemImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *ItemNameText;

	UPROPERTY(meta = (BindWidget))
	class UImage *CurrencyImage;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *CurrencyText;

	UPROPERTY()
	ACommonFunction *CommonFunction;
};
