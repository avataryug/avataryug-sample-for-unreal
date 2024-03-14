// Fill out your copyright notice in the Description page of Project Settings.


#include "AdsButtonsGrid.h"

void UAdsButtonsGrid::NativeConstruct()
{
    Super::NativeConstruct();
}
void UAdsButtonsGrid::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    auto* item = Cast<UAdsListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
    if (AdsButtonList.Num() <= 0)
    {
        AdsButtonList.Add(AdsButton);
        AdsButtonList.Add(AdsButton_1);
    }
    for (int i = 0; i < AdsButtonList.Num(); i++)
    {
        int elementindex = item->StartIndex + i;
        if (elementindex < item->TotalCount)
        {
            //  AdsButtonList[i]->SetButton(item->bundleItem[elementindex],item->panel);
             AdsButtonList[i]->OnRewardItemClick = item->callback;
            AdsButtonList[i]->item =  item->rewardItem[i];
            //  AdsButtonList[i]->RewardNameText->SetText(FText::FromString(item->rewardItem[i].PlacementName));
            AdsButtonList[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            AdsButtonList[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}