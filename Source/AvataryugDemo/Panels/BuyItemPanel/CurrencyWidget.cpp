// Fill out your copyright notice in the Description page of Project Settings.


#include "CurrencyWidget.h"

void UCurrencyWidget::NativeConstruct() { Super::NativeConstruct(); }

void UCurrencyWidget::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UTotalCurrencyData>(ListItemObject);
	if (!item) {
	     UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
    }

    if (item->Code == "CN")
    {
        CurrencyImage->SetBrush(CurrencyCN);
    }

    if (item->Code == "CC")
    {
        CurrencyImage->SetBrush(CurrencyCC);
    }

    if (item->Code == "RM")
    {
        CurrencyImage->SetBrush(ReamMoneyImage);
    }
 
    CurrencyText->SetText(FText::FromString(item->Amount));
}