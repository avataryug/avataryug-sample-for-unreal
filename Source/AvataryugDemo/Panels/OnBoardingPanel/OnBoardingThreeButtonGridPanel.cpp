// Fill out your copyright notice in the Description page of Project Settings.
#include "OnBoardingThreeButtonGridPanel.h"
#include "OnBoardingThree.h"
#include "OnBoardingThreeAvatarButton.h"

void UOnBoardingThreeButtonGridPanel::NativeConstruct()
{
    Super::NativeConstruct();
}

void UOnBoardingThreeButtonGridPanel::NativeOnListItemObjectSet(UObject *ListItemObject)
{
    auto *item = Cast<UListNewItemData>(ListItemObject);
    if (!item)
    {
        UE_LOG(LogTemp, Display, TEXT("Err"));
        return;
    }

    if (OnBoradingThreeButtons.Num() <= 0)
    {
        OnBoradingThreeButtons.Add(OnBoradingThreeButton_1);
        OnBoradingThreeButtons.Add(OnBoradingThreeButton_2);
        OnBoradingThreeButtons.Add(OnBoradingThreeButton_3);
    }
    int startingIndex = item->StartIndex;
    int TotalCount = item->TotalCount;
    TArray<FGetAvatarPresetsResultDataInner> AvatarPresetLists = item->presetLists;
    for (int i = 0; i < OnBoradingThreeButtons.Num(); i++)
    {
        int elementindex = startingIndex + i;
        if (elementindex < TotalCount)
        {
            OnBoradingThreeButtons[i]->SetOnBoardThreeButton(item->OnBoardingThree,AvatarPresetLists[elementindex], item->OnClickButton);
            OnBoradingThreeButtons[i]->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("PresetAvatarButtons--->>ELSE--"))
        }
    }
}
