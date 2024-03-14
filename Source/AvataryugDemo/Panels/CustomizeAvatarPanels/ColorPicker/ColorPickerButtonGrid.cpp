// Fill out your copyright notice in the Description page of Project Settings.

#include "ColorPickerButtonGrid.h"

void UColorPickerButtonGrid::NativeConstruct()
{
    Super::NativeConstruct();
}

void UColorPickerButtonGrid::NativeOnListItemObjectSet(UObject *ListItemObject)
{

    auto *item = Cast<UColorListData>(ListItemObject);
    if (!item)
    {
        UE_LOG(LogTemp, Display, TEXT("Err"));
        return;
    }
    if (PropItemButtons.Num() <= 0)
    {
        PropItemButtons.Add(ColorPickerButton1);
        PropItemButtons.Add(ColorPickerButton2);
        PropItemButtons.Add(ColorPickerButton3);
        PropItemButtons.Add(ColorPickerButton4);
    }
    int startingIndex = item->StartIndex;
    int TotalCount = item->TotalCount;

    TArray<FString> colorlist = item->m_Colors;
    for (int i = 0; i < PropItemButtons.Num(); i++)
    {
        int elementindex = startingIndex + i;
        if (elementindex < TotalCount)
        {
            PropItemButtons[i]->SetButton(item->category, colorlist[elementindex]);
            PropItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            PropItemButtons[i]->SetVisibility(ESlateVisibility::Hidden);
        }
    }
}