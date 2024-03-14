// Fill out your copyright notice in the Description page of Project Settings.


#include "AdsButton.h"

void UAdsButton::NativeConstruct()
{
    Super::NativeConstruct();

    ADP_RewardItemButton->OnClicked.RemoveDynamic(this, &UAdsButton::OnClickRewardItemButton);
    ADP_RewardItemButton->OnClicked.AddDynamic(this, &UAdsButton::OnClickRewardItemButton);
}
void UAdsButton::OnClickRewardItemButton()
{
    OnRewardItemClick.ExecuteIfBound(item);
}