// Fill out your copyright notice in the Description page of Project Settings.


#include "BundleButton.h"

void UBundleButton::NativeConstruct()
{
    Super::NativeConstruct();
    BundleItemBtn->OnClicked.RemoveDynamic(this,&UBundleButton::OnBundlesButtonClicked);
    BundleItemBtn->OnClicked.AddDynamic(this,&UBundleButton::OnBundlesButtonClicked);
}
void UBundleButton::SetButton(FEconomyBundle data, UBundleDetailPanel *panel)
{
    if (data.VirtualCurrency.currencyRewards.Num() > 0)
    {
        BIB_BundleNameText->SetText(FText::FromString(data.DisplayName));
        BIB_BundleCoinText->SetText(FText::FromString(data.VirtualCurrency.currencyRewards[0].Amount));
    } 
    currentData = data;
    bunddetailPanel = panel;
}
void UBundleButton::OnBundlesButtonClicked()
{
      UE_LOG(LogTemp, Display, TEXT("ON BUNDLE--BUTTON CLICKED--->>"));
      bunddetailPanel->SetVisibility(ESlateVisibility::Visible);
      bunddetailPanel->ShowBundlesDetail(currentData);
}