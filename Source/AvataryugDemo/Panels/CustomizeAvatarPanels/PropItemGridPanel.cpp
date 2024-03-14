// Fill out your copyright notice in the Description page of Project Settings.


#include "PropItemGridPanel.h"
#include "PropItemButton.h"
void UPropItemGridPanel::NativeConstruct()
{
  Super::NativeConstruct();
  
}



void UPropItemGridPanel::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UCustomizeListData>(ListItemObject);
	if (!item) {
	     UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
    if(PropItemButtons.Num() <= 0){
            PropItemButtons.Add( PropItemButtons1);
            PropItemButtons.Add( PropItemButtons2);
            PropItemButtons.Add( PropItemButtons3);
            PropItemButtons.Add( PropItemButtons4);
    }
     int startingIndex = item->StartIndex;
     int TotalCount = item->TotalCount;

     if (item->dataType == "EXPRESSION") 
     {
        UE_LOG(LogTemp,Warning,TEXT("LOADING EXPRESSIONS"))
        TArray<FExpression> expressionLists = item->expressionLists;
        for (int i = 0; i < PropItemButtons.Num(); i++)
        {
            //  UE_LOG(LogTemp,Warning,TEXT("PropItemButtons--->>"))
            int elementindex = startingIndex + i;
            if (elementindex < TotalCount)
            {
                // UE_LOG(LogTemp,Warning,TEXT("PropItemButtons--->>222"))
                PropItemButtons[i]->SetButtonExpression(expressionLists[elementindex]);
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                //  UE_LOG(LogTemp,Warning,TEXT("PropItemButtons--->>ELSE--"))
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Hidden); 
            }
        }
    }
    else if (item->dataType == "CLIP") 
    {
        TArray<FClip> clipsLists = item->clipLists;
        for (int i = 0; i < PropItemButtons.Num(); i++)
        {
            int elementindex = startingIndex + i;
            if (elementindex < TotalCount)
            {
                PropItemButtons[i]->SetButtonClip(clipsLists[elementindex]);
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Hidden); 
            }
        }
    }

    else if (item->dataType == "AVATAR") {
      UE_LOG(LogTemp,Warning,TEXT("=================  %d"),TotalCount)
        TArray<FUserAvatar> userAvatars = item->userAvatars;
        for (int i = 0; i < userAvatars.Num(); i++)
        {
            int elementindex = startingIndex + i;
            if (elementindex < TotalCount)
            {
                PropItemButtons[i]->SetButtonAvatar(userAvatars[elementindex]);
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Hidden); 
            }
        }
    }  else  
    {
        TArray<FEconomyItems> currentSelectedItems = item->currentSelectedItems;
        for (int i = 0; i < PropItemButtons.Num(); i++)
        {
            int elementindex = startingIndex + i;
            if (elementindex < TotalCount)
            {
                PropItemButtons[i]->SetButton(currentSelectedItems[elementindex]);
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                PropItemButtons[i]->SetVisibility(ESlateVisibility::Hidden); 
            }
        }
    }
}