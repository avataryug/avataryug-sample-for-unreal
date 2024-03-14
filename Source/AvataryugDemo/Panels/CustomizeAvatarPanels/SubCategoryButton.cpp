// Fill out your copyright notice in the Description page of Project Settings.


#include "SubCategoryButton.h"

void USubCategoryButton::NativeConstruct() 
{
    Super::NativeConstruct();
    CategoryButton->OnClicked.RemoveDynamic(this, &USubCategoryButton::OnCategoryButtonClick);
    CategoryButton->OnClicked.AddDynamic(this, &USubCategoryButton::OnCategoryButtonClick);
}
void USubCategoryButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UCustomizeSubCatListData>(ListItemObject);
	if (!item) {
	     UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
    Cat = item->Category;
    CategoryText->SetText(FText::FromString(item->Category));
    ButtonSizeBox->SetMinDesiredWidth(item->Category.Len() * 30);
    OnClickSubCategory = item->ClickSubCategory;
}

void USubCategoryButton::OnCategoryButtonClick()
{
    OnClickSubCategory.ExecuteIfBound(Cat);
}