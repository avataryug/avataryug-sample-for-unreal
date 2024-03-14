// Fill out your copyright notice in the Description page of Project Settings.

#include "PropItemButton.h"
#include "CustomizeData.h"
#include "ImageUtils.h"
#include "Http.h"
#include "Components/Button.h"
#include <cstddef>

void UPropItemButton::NativeConstruct()
{
    Super::NativeConstruct();
    OnReceiveTexture.BindUFunction(this, "OnLoadImage");

    if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
    }
    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
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

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
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

    if (DataHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADataHolder::StaticClass());
        DataHolder = Cast<ADataHolder>(FoundActor);
        if (DataHolder == nullptr)
        {
            DataHolder = GetWorld()->SpawnActor<ADataHolder>();
        }
    }

    ItemButton->OnClicked.RemoveDynamic(this, &UPropItemButton::OnClickButton);
    ItemButton->OnClicked.AddDynamic(this, &UPropItemButton::OnClickButton);

    APIEvents->OnUpdateUiAfterItemSelect.RemoveDynamic(this, &UPropItemButton::UpdateUiAfterItemSelect);
    APIEvents->OnUpdateUiAfterItemSelect.AddDynamic(this, &UPropItemButton::UpdateUiAfterItemSelect);

    UpdateButtonData();
}
void UPropItemButton::UpdateUiAfterItemSelect()
{
    UpdateButtonData();
}
void UPropItemButton::OnClickButton()
{
    APIEvents->HideLoading();
    if (Category == "EXPRESSION")
    {
        if (AvatarHandler)
        {
            AvatarHandler->ForCustomizeAvatar->SetExpression(ExpressionItem);
        }
    }
    if (Category == "CLIP")
    {
        if (AvatarHandler)
        {
            AvatarHandler->ForCustomizeAvatar->ShowClip(ClipItem);
        }
    }
    if (Category == "PROP")
    {
        if (EconomyItem.displayName == "Custom")
        {
            APIEvents->ShowPanel(EUIPanels::CUSTOMIZEBLENDSHAPE, true);
            APIEvents->HidePanel(EUIPanels::CUSTOMIZEHEAD);
        }
        else
        {
            if (AvatarHandler)
            {
                APIEvents->ShowLoading();
                AvatarHandler->ForCustomizeAvatar->LoadNetworkModel(EconomyItem);
            }
        }
    }
    if (Category == "AVATAR")
    {
    }
}

void UPropItemButton::SetButtonExpression(FExpression item)
{
    // CustomImage->SetVisibility(ESlateVisibility::Hidden);
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    TickImage->SetVisibility(ESlateVisibility::Hidden);
    SelectImage->SetVisibility(ESlateVisibility::Hidden);
    ExpressionItem = item;
    Id = ExpressionItem.ID;
    Category = "EXPRESSION";
    CurrencyText->SetVisibility(ESlateVisibility::Hidden);
    CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
    if (item.DisplayName == "Custom")
    {
        // UE_LOG(LogTemp,Warning,TEXT("SetButton Custom Expression--->>222"))
    }
    else
    {

        UpdateExpData();
    }
}

void UPropItemButton::SetButtonClip(FClip item)
{
    // CustomImage->SetVisibility(ESlateVisibility::Hidden);
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    TickImage->SetVisibility(ESlateVisibility::Hidden);
    SelectImage->SetVisibility(ESlateVisibility::Hidden);
    ClipItem = item;
    Id = ClipItem.ID;
    Category = "CLIP";
    CurrencyText->SetVisibility(ESlateVisibility::Hidden);
    CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
    if (item.DisplayName == "Custom")
    {
    }
    else
    {
        UpdateClipData();
    }
}
void UPropItemButton::UpdateExpData()
{
    if (ExpressionItem.ThumbnailUrl.itemThumbnails.Num() > 0)
    {
        if (AllGraphicsHolder->IsGraphicsPresent(ExpressionItem.ID))
        {
            FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics(ExpressionItem.ID);
            ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
            LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
            CurrencyText->SetVisibility(ESlateVisibility::Hidden);
            CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
            SelectImage->SetVisibility(ESlateVisibility::Hidden);
            if (DataHolder->currentExpDataHolder.ID == ExpressionItem.ID)
            {
                SelectImage->SetVisibility(ESlateVisibility::Visible);
            }
        }
        else
        {
            ULoadTextureFromURL::LoadTexture(ExpressionItem.ThumbnailUrl.itemThumbnails[0].thumbnail_url, OnReceiveTexture);
        }
    }
}
void UPropItemButton::UpdateClipData()
{
    if (ClipItem.ThumbnailsUrl.itemThumbnails.Num() > 0)
    {
        if (AllGraphicsHolder->IsGraphicsPresent(ClipItem.ID))
        {
            FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics(ClipItem.ID);
            ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
            CurrencyText->SetVisibility(ESlateVisibility::Hidden);
            CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
            LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
            SelectImage->SetVisibility(ESlateVisibility::Hidden);
            if (AvatarHandler->ForCustomizeAvatar->currentClip.ID == ClipItem.ID)
            {
                SelectImage->SetVisibility(ESlateVisibility::Visible);
            }
        }
        else
        {
            ULoadTextureFromURL::LoadTexture(ClipItem.ThumbnailsUrl.itemThumbnails[0].thumbnail_url, OnReceiveTexture);
        }
    }
}

void UPropItemButton::SetButtonAvatar(FUserAvatar userAvatar)
{
    Category = "AVATAR";
    thisUserAvatar = userAvatar;
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    TickImage->SetVisibility(ESlateVisibility::Hidden);
    SelectImage->SetVisibility(ESlateVisibility::Hidden);
    CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
    CurrencyText->SetVisibility(ESlateVisibility::Hidden);
    if (userAvatar.ThumbUrls.Num() > 0)
    {
        ULoadTextureFromURL::LoadTexture(userAvatar.ThumbUrls[0].ImageURL, OnReceiveTexture);
    }
}

void UPropItemButton::SetButton(FEconomyItems item)
{
    // CustomImage->SetVisibility(ESlateVisibility::Hidden);
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    TickImage->SetVisibility(ESlateVisibility::Hidden);
    SelectImage->SetVisibility(ESlateVisibility::Hidden);
    EconomyItem = item;
    Id = EconomyItem.iD;
    Category = "PROP";
    if (item.displayName == "Custom")
    {
        LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
        ItemImage->SetVisibility(ESlateVisibility::Visible);
        FSlateBrush Brush;
        //    Brush.TintColor = FSlateColor(FLinearColor(1.0f, 1.0f, 1.0f, 1.0f));
        Brush.SetResourceObject(CustomImage);
        ItemImage->SetBrush(Brush);
        // ItemImage->SetRenderZOrder(3);
        // ItemImage->SetZorder
        // ItemImage->SetBrushFromTexture(CustomImage, false);
        // CustomImage->SetVisibility(ESlateVisibility::Visible);
        // ItemImage->SetBrushFromTexture(CustomImage, true);
        CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
        CurrencyText->SetVisibility(ESlateVisibility::Hidden);
        // ItemImage->SetVisibility(ESlateVisibility::Hidden);
    }
    else
    {
        UpdateButtonData();
    }
}

void UPropItemButton::UpdateButtonData()
{
    CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
    CurrencyText->SetVisibility(ESlateVisibility::Hidden);
    TickImage->SetVisibility(ESlateVisibility::Hidden);
    if (EconomyItem.itemThumbnailsUrl.itemThumbnails.Num() > 0)
    {
        if (AllGraphicsHolder->IsGraphicsPresent(EconomyItem.iD))
        {
            FGraphicsWithID graphisWithid = AllGraphicsHolder->GetGraphics(EconomyItem.iD);
            ItemImage->SetBrushFromTexture(graphisWithid.Texture, false);
            TArray<FEconomyItems> currentSelectedBodyParts = DataHolder->currentSelectedBodyParts;
            SelectImage->SetVisibility(ESlateVisibility::Hidden);
            for (int i = 0; i < currentSelectedBodyParts.Num(); i++)
            {
                if (currentSelectedBodyParts[i].iD == EconomyItem.iD)
                {
                    SelectImage->SetVisibility(ESlateVisibility::Visible);
                }
            }
            LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
        }
        else
        {
            ULoadTextureFromURL::LoadTexture(EconomyItem.itemThumbnailsUrl.itemThumbnails[0].thumbnail_url, OnReceiveTexture);
        }
    }
    if (AvatarHandler->TypeOfMontization == EMonitizeType::Monitize) {
        if (UserInventoryHolder->IsPresentInventory(EconomyItem.iD))
            {
                CurrencyImage->SetVisibility(ESlateVisibility::Hidden);
                CurrencyText->SetVisibility(ESlateVisibility::Hidden);
                TickImage->SetVisibility(ESlateVisibility::Visible);
            }
            else
            {
                CurrencyImage->SetVisibility(ESlateVisibility::Visible);
                CurrencyText->SetVisibility(ESlateVisibility::Visible);
                TickImage->SetVisibility(ESlateVisibility::Hidden);
                if (EconomyItem.virtualCurrency.virtualCurrencys.Num() > 0)
                {
                    CurrencyText->SetText(FText::FromString(EconomyItem.virtualCurrency.virtualCurrencys[0].Amount));
                }
                else
                {
                    CurrencyText->SetText(FText::FromString("0"));
                }
            }
    }
   
}

void UPropItemButton::OnLoadImage(UTexture2D *textures)
{
    ItemImage->SetBrushFromTexture(textures, false);
    AllGraphicsHolder->AddGraphics(textures, Id);
    LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
}
