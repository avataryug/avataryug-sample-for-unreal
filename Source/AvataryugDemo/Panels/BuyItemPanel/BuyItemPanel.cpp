// Fill out your copyright notice in the Description page of Project Settings.
#include "BuyItemPanel.h"
#include "Kismet/GameplayStatics.h"
#include "UserItemManagementAPI/UserItemManagementHandler.h"
#include "TimerManager.h"
#include "JsonObjectConverter.h"
#include "UserAccountManagementAPI/UserAccountManagementAPI.h"

void UBuyItemPanel::NativeConstruct()
{
    Super::NativeConstruct();

    if (AllGraphicsHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAllGraphicsHolder::StaticClass());
        AllGraphicsHolder = Cast<AAllGraphicsHolder>(FoundActor);
    }

    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        if (UserDetailHolder == nullptr)
        {
            UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
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

    CloseButton->OnClicked.RemoveDynamic(this, &UBuyItemPanel::CloseBuyItemPanel);
    CloseButton->OnClicked.AddDynamic(this, &UBuyItemPanel::CloseBuyItemPanel);

    CloseButton1->OnClicked.RemoveDynamic(this, &UBuyItemPanel::CloseBuyItemPanel);
    CloseButton1->OnClicked.AddDynamic(this, &UBuyItemPanel::CloseBuyItemPanel);

    BuyButton->OnClicked.RemoveDynamic(this, &UBuyItemPanel::OnClickBuyItem);
    BuyButton->OnClicked.AddDynamic(this, &UBuyItemPanel::OnClickBuyItem);

    OnGetUserInventoryResult.BindUFunction(this, "GetUserInventoryResult");
    OnInventoryApiError.BindUFunction(this, "InventoryApiError");

    OnGetUserAccountInfoResult.BindUFunction(this, "OnReceiveGetUserAccountInfoResult");
    OnGetUserAccountInfoError.BindUFunction(this, "OnReceiveGetUserAccountInfoError");

    OnPurchaseInstanceResult.BindUFunction(this, "PurchaseInstanceResult");
    OnPurchaseInstanceError.BindUFunction(this, "OnPurchaseError");
}

void UBuyItemPanel::CloseBuyItemPanel()
{
    currentEconomyItem = FEconomyItems();
    if (BuyItemListView)
    {
        BuyItemListView->ClearListItems();
    }
    APIEvents->HidePanel(EUIPanels::BUYITEMS);
}

void UBuyItemPanel::OnClickBuyItem()
{
    currentEconomyItem = FEconomyItems();
    bool isPresent = true;
    APIEvents->ShowLoading();
    for (auto &currenys : currencyWithAmounts)
    {
        if (currenys.Code != "RM")
        {
            for (auto &walet : UserDetailHolder->UserDetails.wallets.wallets)
            {
                if (walet.VirtualCurrency == currenys.Code)
                {
                    if (walet.Amount < currenys.Amount)
                    {
                        isPresent = false;
                    }
                }
            }
        }
    }
    if (isPresent)
    {
        BuyItemQueueList.Empty();
        for (int i = 0; i < BuyItemList.Num(); i++)
        {
            BuyItemQueueList.Add(BuyItemList[i]);
        }
        if (BuyItemQueueList.Num() > 0)
        {
            OnQueueBuyItem();
        }
    }
}

void UBuyItemPanel::LoadBuyPanelData()
{
    BuyItemList.Empty();

    if (DataHolder != nullptr && UserInventoryHolder != nullptr)
    {
        TArray<FEconomyItems> currentItems = DataHolder->currentSelectedBodyParts;
        if (currentItems.Num()>0)
        {
            for (int i = 0; i < currentItems.Num(); i++)
            {
                if (!currentItems[i].displayName.IsEmpty())
                {
                    if (!UserInventoryHolder->IsPresentInventory(currentItems[i].iD))
                    {
                        BuyItemList.Add(currentItems[i]);
                    }
                }
            }
        }
        if (CurrencyListView)
        {
            CurrencyListView->ClearListItems();
        }
        if (BuyItemListView)
        {
            BuyItemListView->ClearListItems();
            for (int i = 0; i < BuyItemList.Num(); i++)
            {
                UBuyItemListData* item = NewObject<UBuyItemListData>();
                item->Index = i;
                item->EconomyItem = BuyItemList[i];
                BuyItemListView->AddItem(item);
            }
        }
        UpdatePrise();
        if (currencyWithAmounts.Num() > 0) 
        {
            for (int i = 0; i < currencyWithAmounts.Num(); i++)
            {
                UTotalCurrencyData* item = NewObject<UTotalCurrencyData>();
                item->Code = currencyWithAmounts[i].Code;
                item->Amount = FString::FromInt(currencyWithAmounts[i].Amount);
                CurrencyListView->AddItem(item);
            }
        }
    }
}

void UBuyItemPanel::UpdatePrise()
{
    currencyWithAmounts.Empty();
    for (int i = 0; i < BuyItemList.Num(); i++)
    {
        if (BuyItemList[i].virtualCurrency.virtualCurrencys.Num() > 0)
        {
            if (!BuyItemList[i].virtualCurrency.virtualCurrencys[0].Amount.IsEmpty())
            {
                AddCurrency(BuyItemList[i].virtualCurrency.virtualCurrencys[0].UserID, FCString::Atoi(*BuyItemList[i].virtualCurrency.virtualCurrencys[0].Amount));
            }
        }
    }
}

void UBuyItemPanel::AddCurrency(FString code, int amount)
{
    bool found = false;
    if (currencyWithAmounts.Num() > 0)
    {
        for (int i = 0; i < currencyWithAmounts.Num(); i++)
        {
            if (currencyWithAmounts[i].Code == code)
            {
                currencyWithAmounts[i].Amount += amount;
                found = true;
                break;
            }
        }
    }
    if (!found)
    {
        FCurrencyWithAmount curAmount;
        curAmount.Amount = amount;
        curAmount.Code = code;
        currencyWithAmounts.Add(curAmount);
    }
}

void UBuyItemPanel::OnQueueBuyItem()
{
    if (BuyItemQueueList.Num() > 0)
    {
        FEconomyItems economyItem = BuyItemQueueList[0];
        currentEconomyItem = economyItem;
        BuyItemQueueList.RemoveAt(0);
        PurchaseItem(economyItem);
    }
    else
    {
        UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
    }
}
void UBuyItemPanel::GetUserInventoryResult(FGetUserInventoryResult result)
{
    UserInventoryHolder->AddUserInventory(result.Data);
    UUserAccountManagementAPI::GetUserAccountInfo(UserDetailHolder->UserDetails.userID, OnGetUserAccountInfoResult, OnGetUserAccountInfoError);
}

void UBuyItemPanel::InventoryApiError(FApiException error)
{
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
}

///////GetUserAccountInfo==================================================================
void UBuyItemPanel::OnReceiveGetUserAccountInfoResult(FGetUserAccountInfoResult result)
{
    FWallets Wallets;
    FString ResponseString = "{";
    ResponseString.Append("\"wallets\":");
    ResponseString.Append(result.Data.Wallet);
    ResponseString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &Wallets,0,0);
    UserDetailHolder->UserDetails.wallets = Wallets;
    APIEvents->UpdateUiAfterItemSelect();
    APIEvents->HideLoading();
    APIEvents->UpdatesUI();
    APIEvents->UpdatesBuyButtonUI();
    APIEvents->UpdatesHeadUI();
    APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
    APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
    this->SetVisibility(ESlateVisibility::Hidden);
}
void UBuyItemPanel::OnReceiveGetUserAccountInfoError(FApiException error)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
}
///////======================================================================================

void UBuyItemPanel::PurchaseItem(FEconomyItems economyItem)
{
    FPurchaseInstanceRequest request;
    request.InstanceID = economyItem.iD;
    request.InstanceType = "ITEM";
    request.Price = FCString::Atoi(*economyItem.virtualCurrency.virtualCurrencys[0].Amount);
    request.VirtualCurrency = economyItem.virtualCurrency.virtualCurrencys[0].UserID;
    request.StoreID = "";
    UUserItemManagementHandler::PurchaseInstance(request, OnPurchaseInstanceResult, OnPurchaseInstanceError);
}

void UBuyItemPanel::PurchaseInstanceResult(FString result)
{
    FGetUserInventoryResultDataInner invItem;
    invItem.InstanceType = "ITEM";
    invItem.DisplayName = currentEconomyItem.displayName;
    invItem.InstanceID = currentEconomyItem.iD;
    UserInventoryHolder->Inventory.Add(invItem);
    OnQueueBuyItem();
    // FTimerHandle TimerHandle_Delay;
    // FTimerManager& TimerManager = GetWorld()->GetTimerManager();
    // TimerManager.SetTimer(TimerHandle_Delay, this, &UBuyItemPanel::AddingDelay, 2.0f, false);

    // LoadBuyPanelData();
}
void UBuyItemPanel::AddingDelay()
{
    OnQueueBuyItem();
    // APIEvents->OnPropButtonClick(true);
    // APIEvents->UpdatesUI();
}
void UBuyItemPanel::OnPurchaseError(FApiException error)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
}