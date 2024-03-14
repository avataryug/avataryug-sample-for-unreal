// Fill out your copyright notice in the Description page of Project Settings.


#include "BuyListItem.h"
#include "Kismet/GameplayStatics.h"

void UBuyListItem::NativeConstruct() 
{ 
	
	Super::NativeConstruct(); 

    if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
    }
	if (CommonFunction == nullptr)
	{
		AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
		CommonFunction = Cast<ACommonFunction>(FoundActor);
		if (CommonFunction == nullptr)
		{
			CommonFunction = GetWorld()->SpawnActor<ACommonFunction>();
		}
	}
}
void UBuyListItem::NativeOnListItemObjectSet(UObject* ListItemObject)
{
    auto* item = Cast<UBuyItemListData>(ListItemObject);
	if (!item)
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
		return;
	}
	int device = CommonFunction->GetPlatformAsInt();

	FEconomyItems economyItem = FEconomyItems();
	economyItem = item->EconomyItem;

		if(!item->EconomyItem.iD.IsEmpty())
		{
			if (AllGraphicsHolder->IsGraphicsPresent(item->EconomyItem.iD))
			{
				FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics( item->EconomyItem.iD);
				ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
			}
			else
			{
				if (economyItem.itemThumbnailsUrl.itemThumbnails.Num() > 0)
				{
					FString url = "";
					for (int i = 0; i < item->EconomyItem.itemThumbnailsUrl.itemThumbnails.Num(); i++)
					{
						if (item->EconomyItem.itemThumbnailsUrl.itemThumbnails[i].device == device)
						{
							url = item->EconomyItem.itemThumbnailsUrl.itemThumbnails[i].thumbnail_url;
						}
					}
					ULoadTextureFromURL::LoadByte("url", [this](UTexture2D* texture)
					{
						ItemImage->SetBrushFromTexture(texture, false);
					});
				}
			}
		}
		
		if(!economyItem.displayName.IsEmpty())
		{
			ItemNameText->SetText(FText::FromString(item->EconomyItem.displayName));
		}
		if (economyItem.virtualCurrency.virtualCurrencys.Num() > 0) 
		{
			if (!economyItem.virtualCurrency.virtualCurrencys[0].Amount.IsEmpty())
			{
				CurrencyText->SetText(FText::FromString(economyItem.virtualCurrency.virtualCurrencys[0].Amount));
			}
			else
			{
				CurrencyText->SetText(FText::FromString("0"));
			}
		}
		else
		{
			CurrencyText->SetText(FText::FromString("0"));
		}
		

}