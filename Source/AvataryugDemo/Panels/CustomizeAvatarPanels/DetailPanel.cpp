// Fill out your copyright notice in the Description page of Project Settings.


#include "DetailPanel.h"
#include "Components/CanvasPanelSlot.h"
#include "Kismet/GameplayStatics.h"
void UDetailPanel::NativeConstruct()
{
  Super::NativeConstruct();

    if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
    }

     if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
        APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
        if(APIEvents)
        {
            APIEvents->OnScreenOrientation.AddDynamic(this,&UDetailPanel::SetDetailPanelOrientation);
        }
    }
   if (EconomyItemHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
        EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
        if (EconomyItemHolder == nullptr)
        {
            EconomyItemHolder = GetWorld()->SpawnActor<AEconomyItemHolder>();
        }
    }
    if (DataHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADataHolder::StaticClass());
        DataHolder = Cast<ADataHolder>(FoundActor);
        if (DataHolder == nullptr)
        {
            DataHolder = GetWorld()->SpawnActor<ADataHolder>();
        }
    }

    if (UserInventoryHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
        UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
        if (UserInventoryHolder == nullptr)
        {
            UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
        }
    }


    CloseButton->OnClicked.RemoveDynamic(this, &UDetailPanel::CloseDetailPanel);
    CloseButton->OnClicked.AddDynamic(this, &UDetailPanel::CloseDetailPanel);

    CloseButton1->OnClicked.RemoveDynamic(this, &UDetailPanel::CloseDetailPanel);
    CloseButton1->OnClicked.AddDynamic(this, &UDetailPanel::CloseDetailPanel);

    BuyButton->OnClicked.RemoveDynamic(this, &UDetailPanel::OnClickBuyButton);
    BuyButton->OnClicked.AddDynamic(this, &UDetailPanel::OnClickBuyButton);
}

void UDetailPanel::OnClickBuyButton()
{
   this->SetVisibility(ESlateVisibility::Hidden);
   APIEvents->ShowPanel(EUIPanels::BUYITEMS, true);
}

void UDetailPanel::CloseDetailPanel()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}

void UDetailPanel::LoadDetailPanelData()
{
    if (DataHolder != nullptr)
    {
        economyItems = DataHolder->currentSelectedBodyPart;
        if (!UserInventoryHolder->IsPresentInventory(economyItems.iD))
        {
            BuyButton->SetVisibility(ESlateVisibility::Visible);
        }
        else
        {
            BuyButton->SetVisibility(ESlateVisibility::Hidden);
        }

        FString allTags = "";

        if (economyItems.tags.tags.Num() > 0)
        {
      	    for ( auto & item : economyItems.tags.tags) 
	        {
                allTags += "#" + item.name + " " ;
            }
        }

        TagsText->SetText(FText::FromString(allTags));
        ItemNameText->SetText(FText::FromString(economyItems.displayName));

        if (economyItems.virtualCurrency.virtualCurrencys.Num() > 0)
        {
            UE_LOG(LogTemp,Display,TEXT("VIRTUAL CURRENCY COUNT > 0------>>>%s"),*economyItems.virtualCurrency.virtualCurrencys[0].UserID);
            CurrencyText->SetText(FText::FromString(economyItems.virtualCurrency.virtualCurrencys[0].Amount));

            if (economyItems.virtualCurrency.virtualCurrencys[0].UserID == "RR")
            {
                CurrencyImage->SetBrush(CurrencyCN);
            }
            if (economyItems.virtualCurrency.virtualCurrencys[0].UserID == "CC")
            {
                CurrencyImage->SetBrush(CurrencyCC);
            }
            if (economyItems.virtualCurrency.virtualCurrencys[0].UserID == "RM")
            {
                CurrencyImage->SetBrush(ReamMoneyImage);
            }
        }
        else
        {
            UE_LOG(LogTemp,Display,TEXT("VIRTUAL CURRENCY COUNT < 0------>>>"));
        }

        if (AllGraphicsHolder->IsGraphicsPresent(economyItems.iD))
        {
            FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics( economyItems.iD);
            ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
        }

        TArray<FEconomyItems> EconomyItems = EconomyItemHolder->EconomyItems;
        TArray<FEconomyItems> tempList;

        if (economyItems.tags.tags.Num() > 0)
        {
            for ( auto & tag : economyItems.tags.tags) 
            {
                for ( auto & item : EconomyItems) 
                {
                    FString NameToFind = tag.name;
                    FTag* FoundStruct = item.tags.tags.FindByPredicate([&](const FTag& MyStruct) { return MyStruct.name == NameToFind; });
                    if (FoundStruct)
                    {
                        FEconomyItems* economyitem = tempList.FindByPredicate([&](const FEconomyItems &MyStruct) {return MyStruct.iD == item.iD;              });
                        if (economyitem == nullptr)
                        {
                            tempList.Add(item);
                        }
                    }
                }
            }
        }

        if (SimilarTagListView)
        {
            SimilarTagListView->ClearListItems();
        }

        for (int i = 0; i < tempList.Num(); i++)
        {
            USameTagListData *item = NewObject<USameTagListData>();
            item->Economyitem = tempList[i];
            SimilarTagListView->AddItem(item);
        }
    }

}

void UDetailPanel::SetDetailPanelOrientation(bool isLandscape)
{
    if(isLandscape)
    {
        UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(FullDetail_Panel->Slot);
        Canvas->SetAnchors(FAnchors(0.0f,0.0f,1.0f,1.0f));
        Canvas->SetOffsets(FMargin(0.0f, 184.0f, 0.0f, 0.0f));
    }
    else
    {
        UCanvasPanelSlot *Canvas = Cast<UCanvasPanelSlot>(FullDetail_Panel->Slot);
        Canvas->SetAnchors(FAnchors(0.0f,0.0f,1.0f,1.0f));
        Canvas->SetOffsets(FMargin(0.0f, 600.0f, 0.0f, 0.0f));
    }
}