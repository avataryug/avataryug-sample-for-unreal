// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailPropItemButton.h"
#include "ImageUtils.h"
#include "CustomizeData.h"
#include "Http.h"
#include "Components/Button.h"
#include <cstddef>

void UDetailPropItemButton::NativeConstruct() 
{ 
	
	Super::NativeConstruct(); 
	if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
    }

	OnReceiveTexture.BindUFunction(this, "OnLoadImage");
	
}
void UDetailPropItemButton::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<USameTagListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
    }
	else
	{
		Id = item->Economyitem.iD;
		if (item->Economyitem.itemThumbnailsUrl.itemThumbnails.Num() > 0)
		{
			if (AllGraphicsHolder->IsGraphicsPresent(item->Economyitem.iD))
			{
				FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics(item->Economyitem.iD);
				ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
				CurrencyText->SetText(FText::FromString(item->Economyitem.virtualCurrency.virtualCurrencys[0].Amount));
				// CurrencyText->(FText::FromString(items->CurrencyAmount));
				// LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
			}
			else 
			{
				// UE_LOG(LogTemp, Display, TEXT("CUrrencyAmount---- %s"),*EconomyItem.VirtualCurrency.virtualCurrencys[0].Amount);
				// FString amountString = FString::FromInt(EconomyItem.RealCurrency);
				CurrencyText->SetText(FText::FromString(item->Economyitem.virtualCurrency.virtualCurrencys[0].Amount));
				// CurrencyText->SetText(FText::FromString(EconomyItem.VirtualCurrency.virtualCurrencys[0].Amount));
				ULoadTextureFromURL::LoadTexture(item->Economyitem.itemThumbnailsUrl.itemThumbnails[0].thumbnail_url,OnReceiveTexture);
			}
		}
	}
}

void UDetailPropItemButton::OnLoadImage(UTexture2D *textures)
{
	ItemImage->SetBrushFromTexture(textures, false);
    AllGraphicsHolder->AddGraphics(textures, Id) ;
    // LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
}
