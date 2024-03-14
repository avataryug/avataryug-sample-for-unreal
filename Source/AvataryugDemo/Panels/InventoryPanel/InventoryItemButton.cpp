// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryItemButton.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"

void UInventoryItemButton::NativeConstruct()
{
    Super::NativeConstruct();

    ConsumeButton->OnClicked.RemoveDynamic(this, &UInventoryItemButton::OnClickConsumeButton);
    ConsumeButton->OnClicked.AddDynamic(this, &UInventoryItemButton::OnClickConsumeButton);
}

void UInventoryItemButton::OnClickConsumeButton() 
{
  UE_LOG(LogTemp, Display, TEXT("OnClickInventoryItemButton2222"));
  InventoryItemClick.ExecuteIfBound(item);
}
void UInventoryItemButton::SetButtons(FOnInventoryItemClick callback,FGetUserInventoryResultDataInner _item)
{
  InventoryItemClick = callback;
  item = _item;
}
void UInventoryItemButton:: NativeOnListItemObjectSet(UObject* ListItemObject)
{
   auto* items = Cast<UInvetoryItemListData>(ListItemObject);
	if (!items) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
        // APIEvents->HideLoading();
		return;
	}
  else
  {
    ItemName->SetText(FText::FromString(items->data.DisplayName));
    ItemID->SetText(FText::FromString(items->data.ID));
    InventoryItemClick = items->callback;
    item = items->data;
  }
}