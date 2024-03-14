// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/IUserObjectListEntry.h"
#include "Components/TextBlock.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "StoreData.h"
#include "StorePanelButton.generated.h"



UCLASS()
class UStoreListData : public UObject {
	GENERATED_BODY()
public:
	int32 Index;
	FMyContainerBase currentItem;
	UPROPERTY()
	FOnSelectedIndex StoreIndexReceived;
};
/**
 * 
 */
UCLASS()
class AVATARYUGDEMO_API UStorePanelButton : public UUserWidget,public IUserObjectListEntry
{
	GENERATED_BODY()

	protected:
	void NativeConstruct() override;

	virtual void NativeOnListItemObjectSet(UObject* ListItemObject) override;

	public:

	UPROPERTY(meta = (BindWidget))
    class UButton *StoreItemButton;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *CoinAmountText;

	UPROPERTY(meta = (BindWidget))
	class UTextBlock *PriceAmountText;

	UFUNCTION()
	void OnButtonClick();

	int32 itemIndex;

	UPROPERTY()
	FOnSelectedIndex SelectedIndexReceived;


};

