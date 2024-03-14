// Fill out your copyright notice in the Description page of Project Settings.

#include "ContainerButtonGrid.h"
#include "ContainersData.h"
#include "ContainerButton.h"

void UContainerButtonGrid::NativeConstruct()
{
    Super::NativeConstruct();
}

void UContainerButtonGrid::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    auto *item = Cast<UContainerListData>(ListItemObject);
    if (!item)
    {
        UE_LOG(LogTemp, Display, TEXT("Err"));
        return;
    }
    if (ContainersButtonList.Num() <= 0)
    {
        ContainersButtonList.Add(ContainersButton);
        ContainersButtonList.Add(ContainersButton1);
    }
    for (int i = 0; i < ContainersButtonList.Num(); i++)
    {
        int elementindex = item->StartIndex + i;
        if (elementindex < item->TotalCount)
        {
            ContainersButtonList[i]->SetButton(item->Containers[elementindex],item->panel);
            ContainersButtonList[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            ContainersButtonList[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}