// Fill out your copyright notice in the Description page of Project Settings.

#include "InventoryPanel.h"
#include "Components/Button.h"
#include "UserItemManagementAPI/UserItemManagementModels.h"
#include "EconomyAPI/EconomyHandler.h"
#include "Kismet/GameplayStatics.h"
#include "JsonObjectWrapper.h"
#include "InventoryItemButton.h"

void UInventoryPanel::NativeConstruct()
{
    Super::NativeConstruct();
    OnInvebtoryItemClick.BindUFunction(this, "OnClickInventoryItemButton");

    BackButton->OnClicked.RemoveDynamic(this, &UInventoryPanel::OnClickBackButton);
    BackButton->OnClicked.AddDynamic(this, &UInventoryPanel::OnClickBackButton);

    OnEconomyContainerByIDResult.BindUFunction(this, "GetEconomyContainerByIDReply");
    OnEconomyContainerByIDApiError.BindUFunction(this, "GetEconomyContainerByIDError");

    OnConsumeInstanceResult.BindUFunction(this, "GetConsumeInstanceReply");
    OnConsumeInstanceApiError.BindUFunction(this, "GetConsumeInstancetError");

    OnGrantInstanceToUserResult.BindUFunction(this, "GetGrantInstanceToUserReply");
    OnGrantInstanceToUserApiError.BindUFunction(this, "GetGrantInstanceToUserApiError");

    OnUserInventoryResult.BindUFunction(this, "GetUserInventoryReply");
    OnUserInventoryApiError.BindUFunction(this, "GetUserInventoryError");

    OnUserAccountInfoResult.BindUFunction(this, "GetUserAccountInfoReply");
    OnUserAccountInfoApiError.BindUFunction(this, "GetUserAccountInfoError");

    OnConsumeBundleInstanceResult.BindUFunction(this, "GetConsumeBundleInstanceReply");
    OnConsumeBundleInstanceApiError.BindUFunction(this, "GetConsumeBundleInstancetError");

    OnGetEconomyBundleByIDResult.BindUFunction(this, "GetEconomyBundleByIDReply");
    OnGetEconomyBundleByIDApiError.BindUFunction(this, "GetEconomyBundleByIDError");

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
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
    if (UserInventoryHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
        UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
        if (UserInventoryHolder == nullptr)
        {
            UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
        }
    }
}
void UInventoryPanel::OnClickBackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    // APIEvents->ShowPanel(EUIPanels::HOME, true);
}
void UInventoryPanel::LoadInventoryData()
{
    //  UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnUserInventoryResult, OnUserInventoryApiError);
    // TArray<FGetUserInventoryResultDataInner> invenoryItems = UserInventoryHolder->GetInventoryList();

    inventory.Empty();
    // InventoryItemButtonList.Empty();

    for (const auto &item : UserInventoryHolder->GetInventoryList())
    {
        if (item.Count > 0 && item.InstanceType != "ITEM")
        {
            inventory.Add(item);
        }
    }

    // if (InventoryItemButtonList.Num() <= 0)
    // {
    //     UE_LOG(LogTemp, Display, TEXT("IF LOAD INVENTORY  DATA--->>%d"), inventory.Num());
    //     //   UE_LOG(LogTemp, Display, TEXT("ERROR ON GET ECONOMY CONTAINER--->>%s"), *error.ErrorMessage);
    //     for (int i = 0; i < inventory.Num(); i++)
    //     {
    //         UE_LOG(LogTemp, Display, TEXT("invenoryItems"));
    //         UUserWidget *widget = CreateWidget(this, InventoryItemButton);
    //         InventoryItemParent->AddChildToVerticalBox(widget);
    //         UInventoryItemButton *buttons = Cast<UInventoryItemButton>(widget);
    //         buttons->ItemName->SetText(FText::FromString(inventory[i].DisplayName));
    //         buttons->ItemID->SetText(FText::FromString(inventory[i].ID));
    //         buttons->SetButtons(OnInvebtoryItemClick, inventory[i]);
    //         InventoryItemButtonList.Add(buttons);
    //     }

    // }
    // else
    // {
    //     UE_LOG(LogTemp, Display, TEXT("ELSE LOAD INVENTORY  DATA-11111-->>%d"), inventory.Num());
    //     if (InventoryItemButtonList.Num() <= inventory.Num())
    //     {
    //          UE_LOG(LogTemp, Display, TEXT("ELSE LOAD INVENTORY  DATA-2222-->>"));
    //         for (int i = 0; i < inventory.Num(); i++)
    //         {
    //             InventoryItemButtonList[i]->ItemName->SetText(FText::FromString(inventory[i].DisplayName));
    //             InventoryItemButtonList[i]->ItemID->SetText(FText::FromString(inventory[i].ID));
    //             InventoryItemButtonList[i]->SetButtons(OnInvebtoryItemClick, inventory[i]);
    //         }
    //     }
    //     else
    //     {
    //         //  UE_LOG(LogTemp, Display, TEXT("ELSE LOAD INVENTORY  DATA-33333-->>"));
    //         for (int i = 0; i < inventory.Num(); i++)
    //         {
    //             if (InventoryItemButtonList.Num() - 1 < inventory.Num())
    //             {
    //                 InventoryItemButtonList[i]->ItemName->SetText(FText::FromString(inventory[i].DisplayName));
    //                 InventoryItemButtonList[i]->ItemID->SetText(FText::FromString(inventory[i].ID));
    //                 InventoryItemButtonList[i]->SetButtons(OnInvebtoryItemClick, inventory[i]);
    //                  UE_LOG(LogTemp, Display, TEXT("ELSE LOAD INVENTORY  DATA-4444-->>"));
    //             }
    //             else
    //             {
    //                 UUserWidget *widget = CreateWidget(this, InventoryItemButton);
    //                 InventoryItemParent->AddChildToVerticalBox(widget);
    //                 UInventoryItemButton *buttons = Cast<UInventoryItemButton>(widget);
    //                 buttons->ItemName->SetText(FText::FromString(inventory[i].DisplayName));
    //                 buttons->ItemID->SetText(FText::FromString(inventory[i].ID));
    //                 buttons->SetButtons(OnInvebtoryItemClick, inventory[i]);
    //                 InventoryItemButtonList.Add(buttons);

    //                  UE_LOG(LogTemp, Display, TEXT("ELSE LOAD INVENTORY  DATA-5555-->>"));
    //             }
    //         }
    //     }
    // }

    if (InvetroyItemListView)
    {
        InvetroyItemListView->ClearListItems();
    }
    for (int i = 0; i < inventory.Num(); i++)
    {
        UInvetoryItemListData *item = NewObject<UInvetoryItemListData>();
        item->data = inventory[i];
        item->callback = OnInvebtoryItemClick;
        InvetroyItemListView->AddItem(item);
    }
}
void UInventoryPanel::OnClickInventoryItemButton(FGetUserInventoryResultDataInner item)
{
    UE_LOG(LogTemp, Display, TEXT("OnClickInventoryItemButton%s"), *item.InstanceType);
    currentItem = item;
    APIEvents->ShowLoading();
    if (item.InstanceType == "CONTAINER")
    {

        UEconomyHandler::GetEconomyContainerByID(item.InstanceID, OnEconomyContainerByIDResult, OnEconomyContainerByIDApiError);
    }
    if (item.InstanceType == "BUNDLES")
    {
        UEconomyHandler::GetEconomyBundleByID(item.InstanceID, OnGetEconomyBundleByIDResult, OnGetEconomyBundleByIDApiError);
    }
}
FContainerBundleContents UInventoryPanel::GetContainerContents(FGetEconomyContainerByIDResult &Result)
{
    FContainerBundleContents ContainersCont;
    FJsonObjectConverter::JsonObjectStringToUStruct(Result.Data.ContainerContents, &ContainersCont,0,0);
    //   FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &loginResult);
    return ContainersCont;
}
FContainerBundleContents UInventoryPanel::GetBundleContents(FGetEconomyBundleByIDResult &Result)
{
    FContainerBundleContents BundleCont;
    FJsonObjectConverter::JsonObjectStringToUStruct(Result.Data.BundleContents, &BundleCont,0,0);
    return BundleCont;
}
void UInventoryPanel::GetEconomyContainerByIDReply(FGetEconomyContainerByIDResult result)
{
    containerItem = result;
    UE_LOG(LogTemp, Display, TEXT("ON GET ECONOMY CONTAINER--->>%s"), *result.Status);
    FConsumeInstanceRequest request;
    // request.UserID = currentItem.UserID;
    request.InstanceID = currentItem.ID;
    request.InstanceCount = 1;
    UUserItemManagementHandler::ConsumeInstance(request, OnConsumeInstanceResult, OnConsumeInstanceApiError);
}
void UInventoryPanel::GetEconomyContainerByIDError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ERROR ON GET ECONOMY CONTAINER--->>%s"), *error.ErrorMessage);
}
void UInventoryPanel::GetConsumeInstanceReply(FConsumeInstanceResult result)
{
    TArray<FGrantInstanceToUserRequestInstanceIDsInner> items;
    FContainerBundleContents containerContents = GetContainerContents(containerItem);

    for (FContainerBase Item : containerContents.Bundles)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "BUNDLES";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Container)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "CONTAINER";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Items)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "ITEM";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Currencies)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "CURRENCY";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Droptable)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "DROPTABLE";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }

    UE_LOG(LogTemp, Display, TEXT("ON CONSUME --->>%d"), *result.Status);
    UE_LOG(LogTemp, Display, TEXT("ITEMS COUNT  --->>%d"), items.Num());

    FGrantInstanceToUserRequest request;
    request.InstanceIDs = items;

    UUserItemManagementHandler::GrantInstanceToUser(request, OnGrantInstanceToUserResult, OnGrantInstanceToUserApiError);
}
void UInventoryPanel::GetConsumeInstancetError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("ERROR ON CONSUME--->>%s"), *error.ErrorMessage);
}
void UInventoryPanel::GetGrantInstanceToUserReply(FGrantInstanceToUserResult result)
{

    UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER SUCCESS-->>%s"), *result.Message);
    UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnUserInventoryResult, OnUserInventoryApiError);
}
void UInventoryPanel::GetGrantInstanceToUserError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER ERROR-->>%s"), *error.ErrorMessage);
}
void UInventoryPanel::GetUserInventoryReply(FGetUserInventoryResult result)
{
    // APIEvents->HideLoading();
    UserInventoryHolder->AddUserInventory(result.Data);
    UE_LOG(LogTemp, Display, TEXT("   INVENTORY REPLY  --->>%s"), *result.Status);

    UUserAccountManagementAPI::GetUserAccountInfo(UserDetailHolder->UserDetails.userID, OnUserAccountInfoResult, OnUserAccountInfoApiError);
}
void UInventoryPanel::GetUserInventoryError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("   INVENTORY ERROR  --->>%s"), *error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
}
void UInventoryPanel::GetUserAccountInfoReply(FGetUserAccountInfoResult result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info -->>%s"), *result.Status);
    APIEvents->ShowErrorNotification(FString::FromInt(result.Code), "CONTAINER PURCHASED ");

    LoadInventoryData();
    UE_LOG(LogTemp, Display, TEXT("LOADING AGAIN INVENTORY DATA zz -->>"));
}
void UInventoryPanel::GetUserAccountInfoError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info  Erroe -->>%s"), *error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
}
void UInventoryPanel::GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result)
{
    bundleItem = result;
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID SUCCESS--->>%s"), *result.Status);
    FConsumeInstanceRequest request;
    // request.UserID = currentItem.UserID;
    request.InstanceID = currentItem.ID;
    request.InstanceCount = 1;
    UUserItemManagementHandler::ConsumeInstance(request, OnConsumeBundleInstanceResult, OnConsumeBundleInstanceApiError);
    // BDI_PriceText->SetText(FText::FromString(result.Data.DisplayName));
    //  APIEvents->HideLoading();
}
void UInventoryPanel::GetEconomyBundleByIDError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID--->>%s"), *error.ErrorMessage);
    APIEvents->HideLoading();
}
void UInventoryPanel::GetConsumeBundleInstanceReply(FConsumeInstanceResult result)
{
    TArray<FGrantInstanceToUserRequestInstanceIDsInner> items;
    FContainerBundleContents containerContents = GetBundleContents(bundleItem);

    for (FContainerBase Item : containerContents.Bundles)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "BUNDLES";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Container)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "CONTAINER";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Items)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "ITEM";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Currencies)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "CURRENCY";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }
    for (FContainerBase Item : containerContents.Droptable)
    {
        FGrantInstanceToUserRequestInstanceIDsInner NewItem;
        NewItem.InstanceID = Item.UserID;
        NewItem.InstanceType = "DROPTABLE";
        NewItem.Quantity = FCString::Atoi(*Item.Quantity);
        items.Add(NewItem);
    }

    UE_LOG(LogTemp, Display, TEXT("ON CONSUME -BUNDLES-->>%d"), *result.Status);
    UE_LOG(LogTemp, Display, TEXT("ITEMS COUNT  -BUNDLES-->>%d"), items.Num());

    FGrantInstanceToUserRequest request;
    request.InstanceIDs = items;

    UUserItemManagementHandler::GrantInstanceToUser(request, OnGrantInstanceToUserResult, OnGrantInstanceToUserApiError);
}
void UInventoryPanel::GetConsumeBundleInstancetError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("ERROR ON CONSUME-BUNDLES->>%s"), *error.ErrorMessage);
}