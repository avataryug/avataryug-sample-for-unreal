// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerDetailPanel.h"
#include "ContainerDetailButton.h"
#include "Components/ListView.h"
#include "CoreUObject.h"
#include "Core.h"
#include "Engine.h"
#include "ContainersData.h"
void UContainerDetailPanel::NativeConstruct()
{
    Super::NativeConstruct();

    CDP_BackButton->OnClicked.RemoveDynamic(this,&UContainerDetailPanel::OnClickCDP_BackButton);
    CDP_BackButton->OnClicked.AddDynamic(this,&UContainerDetailPanel::OnClickCDP_BackButton);

    CDP_BuyButton->OnClicked.RemoveDynamic(this,&UContainerDetailPanel::OnClickCDP_BuyButton);
    CDP_BuyButton->OnClicked.AddDynamic(this,&UContainerDetailPanel::OnClickCDP_BuyButton);

    OnPurchaseInstanceResult.BindUFunction(this,"PurchaseInstanceReply");
    OnPurchaseInstanceError.BindUFunction(this,"PurchaseError");

    OnGetUserInventoryResult.BindUFunction(this,"UserInventoryReply");
    OnInventoryApiError.BindUFunction(this,"InventoryApiError");

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

    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        if (UserDetailHolder == nullptr)
        {
            UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
        }
    }
}
void UContainerDetailPanel::LoadDetailContainers(FContainerDataClass itemData)
{
    APIEvents->ShowLoading();
    containerbases.Empty();
    containerContents.Empty();
    container = itemData;
    virtualCurrrency = itemData.VirtualCurrency;
    containerContents.Add(itemData.containerContents);


    for (FContainerBundleContents& BundleContent : containerContents)
    {
        for (FContainerBase& Bundle : BundleContent.Bundles)
        {
            Bundle.containerType = "BUNDLES";
            containerbases.Add(Bundle);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD CONTAINER DETAIL DATA--->>%s"), *Bundle.containerType);
        }
    }
    for (FContainerBundleContents& ContainerContent : containerContents)
    {
        for (FContainerBase& Container : ContainerContent.Container)
        {
            Container.containerType = "CONTAINER";
            containerbases.Add(Container);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD CONTAINER DETAIL DATA--->>%s"), *Container.containerType);
        }
    }
    for (FContainerBundleContents& CurrencyContent : containerContents)
    {
        for (FContainerBase& Currency : CurrencyContent.Currencies)
        {
            Currency.containerType = "CURRENCY";
            containerbases.Add(Currency);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD CONTAINER DETAIL DATA--->>%s"), *Currency.containerType);
        }
    }

    for (FContainerBundleContents& DroptableContent : containerContents)
    {
        for (FContainerBase& Droptable : DroptableContent.Droptable)
        {
            Droptable.containerType = "DROPTABLE";
            containerbases.Add(Droptable);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD CONTAINER DETAIL DATA--->>%s"), *Droptable.containerType);
        }
    }
    for (FContainerBundleContents& ItemContent : containerContents)
    {
        for (FContainerBase& Items : ItemContent.Items)
        {
            Items.containerType = "ITEM";
            containerbases.Add(Items);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD CONTAINER DETAIL DATA--->>%s"), *Items.containerType);
        }
    }

    if(ContainerDetailItemListView)
    {
        ContainerDetailItemListView->ClearListItems();
    }

    for(int i = 0 ; i < containerbases.Num();i++ )
    {
        UContainerDetailListData *item = NewObject<UContainerDetailListData>();
        item->data = containerbases[i];
        ContainerDetailItemListView->AddItem(item);
    }
}
void UContainerDetailPanel::OnClickCDP_BackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}

bool UContainerDetailPanel:: IsContainerEmpty(const FContainerDataClass& cont)
{
    return cont.Status == 0
    && cont.DisplayName.IsEmpty()
    && cont.ContainerCategory.IsEmpty()
    && cont.Description.IsEmpty()
    && cont.Tags.IsEmpty()
    && cont.ContainerImageUrl.IsEmpty()
    && cont.IsStackable == 0
    && cont.IsLimitedEdition == 0
    && cont.LimitedEditionIntialCount == 0
    && cont.Entitlement.IsEmpty()
    && IsContainerSettingEmpty(cont.containerSettings)
    && IsContainerBundleContentsEmpty(cont.containerContents)
    && IsVirtualCurrencyRewardEmpty(cont.VirtualCurrency)
    && cont.RealCurrency == 0
    && cont.CustomMetaData.IsEmpty()
    && cont.ID.IsEmpty();
}
bool UContainerDetailPanel::IsContainerSettingEmpty(const FContainerSetting& setting)
{
    return setting.LockedID.IsEmpty()
    && setting.ContainerSettings.IsEmpty()
    && setting.ContainerType.IsEmpty()
    && setting.LockedID.IsEmpty()
    && setting.LockedItemID.IsEmpty();

}
bool UContainerDetailPanel::IsContainerBundleContentsEmpty(const FContainerBundleContents& contents)
{
    return contents.Bundles.Num() == 0
    && contents.Container.Num() == 0
    && contents.Currencies.Num() == 0
     && contents.Droptable.Num() == 0
      && contents.Items.Num() == 0;

}
bool UContainerDetailPanel::IsVirtualCurrencyRewardEmpty(const FVirtualCurrencyReward& reward)
{
    return reward.currencyRewards.Num() == 0;
}
void UContainerDetailPanel::OnClickCDP_BuyButton()
{
    APIEvents->ShowLoading();
    // if(container != nullptr)
    // {
    //     if (!container.containerSettings.LockedID.IsEmpty())
    //     {
        //    if (UserInventoryHolder->IsPresentInventory(container.containerSettings.LockedID))
    //         {
    //             UE_LOG(LogTemp, Display, TEXT(" CONTAINER DETAIL DATA IS PRESENT--->>"));
    //         }
    //         else
    //         {
    //             UE_LOG(LogTemp, Display, TEXT(" CONTAINER DETAIL DATA IS NOT PRESENT--->>"));
    //         }
    //     }
      
    // }
    // else
    // {
    //     UE_LOG(LogTemp, Display, TEXT(" CONTAINER  IS EMPTY--->>"));
    // }

    if (!IsContainerEmpty(container))
    {
        UE_LOG(LogTemp, Display, TEXT(" CONTAINER  IS NOT EMPTY--->>"));
        if (!container.containerSettings.LockedID.IsEmpty())
        {
           if (UserInventoryHolder->IsPresentInventory(container.containerSettings.LockedID))
            {
                UE_LOG(LogTemp, Display, TEXT(" CONTAINER DETAIL DATA IS PRESENT--->>"));
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT(" CONTAINER DETAIL DATA IS NOT PRESENT--->>"));
            }
        }
        else
        {
            UE_LOG(LogTemp, Display, TEXT(" CONTAINER DETAIL --->>%s"),*container.containerSettings.LockedID);

            FString vc = container.VirtualCurrency.currencyRewards[0].UserID;
            int32 price = FCString::Atoi(*container.VirtualCurrency.currencyRewards[0].Amount);

            FPurchaseInstanceRequest request;
            // request.UserID = UserDetailHolder->UserDetails.userID;
            request.InstanceID = container.ID;
            request.InstanceType = "CONTAINER";
            request.Price =  price;
            request.VirtualCurrency  = vc;
            request.StoreID = "";
            UUserItemManagementHandler::PurchaseInstance(request, OnPurchaseInstanceResult,OnPurchaseInstanceError);
        }
    }
    else
    {
         APIEvents->HideLoading();
        UE_LOG(LogTemp, Display, TEXT(" CONTAINER  IS  EMPTY--->>"));
    }

}
void UContainerDetailPanel::PurchaseInstanceReply(FString result)
{
    UE_LOG(LogTemp, Display, TEXT("THE PURCHASE SUCCESS-->>%s"),*result);
    UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
}
void UContainerDetailPanel::PurchaseError(FApiException error)
{
     APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE PURCHASE ERROR-->>%s"),*error.ErrorMessage);
}
void UContainerDetailPanel::UserInventoryReply(FGetUserInventoryResult result)
{
    APIEvents->HideLoading();
    this->SetVisibility(ESlateVisibility::Hidden);
    UserInventoryHolder->AddUserInventory(result.Data);
    APIEvents->ShowErrorNotification(" ","CONTAINER PURCHASED");
    
    UE_LOG(LogTemp, Display, TEXT("Store Invetroy Call------>>%s"),*result.Status);
}
void UContainerDetailPanel::InventoryApiError(FApiException error)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
    UE_LOG(LogTemp, Display, TEXT("Store Invetroy Call------>>%s"),*error.ErrorMessage);
}