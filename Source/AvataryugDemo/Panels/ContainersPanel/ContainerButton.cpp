// Fill out your copyright notice in the Description page of Project Settings.

#include "ContainerButton.h"
#include "ContainersData.h"
void UContainerButton::NativeConstruct()
{
    Super::NativeConstruct();
   
    CIB_ContainerItemButton->OnClicked.RemoveDynamic(this,&UContainerButton::OnContainerButtonClicked);
    CIB_ContainerItemButton->OnClicked.AddDynamic(this,&UContainerButton::OnContainerButtonClicked);
}
void UContainerButton::SetButton(FContainerDataClass data,UContainerDetailPanel *panel)
{
 
    if (data.VirtualCurrency.currencyRewards.Num() > 0)
    {
        ContainerNameText->SetText(FText::FromString(data.DisplayName));
        CIB_priceText->SetText(FText::FromString(data.VirtualCurrency.currencyRewards[0].Amount));
    }
   currentData = data;
   contdetailPanel = panel;
}
void UContainerButton::OnContainerButtonClicked()
{
    UE_LOG(LogTemp, Display, TEXT("ON Container--BUTTON CLICKED--->>"));
    contdetailPanel->SetVisibility(ESlateVisibility::Visible);
    contdetailPanel->LoadDetailContainers(currentData);
}