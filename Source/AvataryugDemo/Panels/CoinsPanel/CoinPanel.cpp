// Fill out your copyright notice in the Description page of Project Settings.

#include "CoinPanel.h"

void UCoinPanel::NativeConstruct()
{
	Super::NativeConstruct();
}

void UCoinPanel::NativeOnListItemObjectSet(UObject *ListItemObject)
{
	auto *items = Cast<UCurrencyItemData>(ListItemObject);
	if (!items)
	{
		UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}

	CurrencyAmount->SetText(FText::FromString(items->CurrencyAmount));
	if (items->CurrencyCode == "CN")
	{
		CurrencyImage->SetBrush(CNImage);
	}
	if (items->CurrencyCode == "CC")
	{
		CurrencyImage->SetBrush(CCImage);
	}
}
