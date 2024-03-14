// Fill out your copyright notice in the Description page of Project Settings.


#include "BundleButtonGrid.h"


void UBundleButtonGrid::NativeConstruct()
{
    Super::NativeConstruct();
}

void UBundleButtonGrid::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UBundleListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
	if (BundlesButtonList.Num() <= 0)
    {
        BundlesButtonList.Add(WBP_BundlesItemButton);
        BundlesButtonList.Add(WBP_BundlesItemButton_1);
    }
    for (int i = 0; i < BundlesButtonList.Num(); i++)
    {
        int elementindex = item->StartIndex + i;
        if (elementindex < item->TotalCount)
        {
            BundlesButtonList[i]->SetButton(item->bundleItem[elementindex],item->panel);
            BundlesButtonList[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            BundlesButtonList[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
   //   UE_LOG(LogTemp, Display, TEXT("CreListItem%s"),*item->testInt.TemplateID);
	//FEconomyItems* Item = Cast<FEconomyItems>(ListItemObject);

}