// Fill out your copyright notice in the Description page of Project Settings.


#include "StorePanelButton.h"

void UStorePanelButton::NativeConstruct()
{
	Super::NativeConstruct();  

	StoreItemButton->OnClicked.RemoveDynamic(this, &UStorePanelButton::OnButtonClick);
	StoreItemButton->OnClicked.AddDynamic(this, &UStorePanelButton::OnButtonClick);
}

void UStorePanelButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UStoreListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
	CoinAmountText->SetText(FText::FromString(item->currentItem.Quantity));
	itemIndex = item->Index;
	SelectedIndexReceived =  item->StoreIndexReceived;
}

void UStorePanelButton::OnButtonClick()
{
	UE_LOG(LogTemp, Display, TEXT("ON BUTTON CLICKED--->> %d"),itemIndex);
	SelectedIndexReceived.Broadcast(itemIndex);
}

