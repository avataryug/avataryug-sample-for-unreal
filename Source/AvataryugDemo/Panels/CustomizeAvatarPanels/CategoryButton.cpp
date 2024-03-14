// Fill out your copyright notice in the Description page of Project Settings.


#include "CategoryButton.h"
#include "Components/Button.h"
#include "../../Utilitys/APIEvents.h"
#include "Components/Image.h"
void UCategoryButton::NativeConstruct()
{
    Super::NativeConstruct();

    CatButton->OnClicked.RemoveDynamic(this, &UCategoryButton::OnClickCategoryButton);
    CatButton->OnClicked.AddDynamic(this, &UCategoryButton::OnClickCategoryButton);

    SelectedImage->SetVisibility(ESlateVisibility::Hidden);
    FillImage->SetVisibility(ESlateVisibility::Hidden);
    OutlineImage->SetVisibility(ESlateVisibility::Visible);
}

void UCategoryButton::OnClickCategoryButton()
{
    OnClickMainCategory.Broadcast(category);
}

void UCategoryButton::SetButton(int index, FString _category,FOnClickMainCategory _onClickMainCat) 
{
    UE_LOG(LogTemp, Display, TEXT("Category------>>>%s    %d"), *_category,CategoryButtonData.Num());
    for (int i = 0; i < CategoryButtonData.Num(); i++)
    {
        // UE_LOG(LogTemp, Display, TEXT("Category------>>>%s"), *_category);
        if(CategoryButtonData[i].Category == _category)
        {
          UE_LOG(LogTemp, Display, TEXT("SetButton %d  %s   "), i, *CategoryButtonData[i].Category );
            OutlineImage->SetBrush(CategoryButtonData[i].ButtonImage);
            FillImage->SetBrush(CategoryButtonData[i].ButtonPressImage);
        }
    }
    OnClickMainCategory = _onClickMainCat;
    category = _category;
}
void UCategoryButton::SetSelectVisible(FString _category)
{
    FillImage->SetVisibility(ESlateVisibility::Hidden);
    OutlineImage->SetVisibility(ESlateVisibility::Visible);
    SelectedImage->SetVisibility(ESlateVisibility::Hidden);

    if (category == _category)
    {
        OutlineImage->SetVisibility(ESlateVisibility::Hidden);
        FillImage->SetVisibility(ESlateVisibility::Visible);
    }
}