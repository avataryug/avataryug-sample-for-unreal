// Fill out your copyright notice in the Description page of Project Settings.


#include "BundleDetailPanel.h"
#include "BundleDetailButton.h"

void UBundleDetailPanel::NativeConstruct()
{

    BDP_BackButton->OnClicked.RemoveDynamic(this,&UBundleDetailPanel::OnClickBDP_BackButton);
    BDP_BackButton->OnClicked.AddDynamic(this,&UBundleDetailPanel::OnClickBDP_BackButton);

    BDP_BuyButton->OnClicked.RemoveDynamic(this,&UBundleDetailPanel::BuyBundles);
    BDP_BuyButton->OnClicked.AddDynamic(this,&UBundleDetailPanel::BuyBundles);

    OnPurchaseInstanceResult.BindUFunction(this, "GetPurchaseInstanceReply");
    OnPurchaseInstanceApiError.BindUFunction(this, "GetPurchaseInstanceError");

    OnUserInventoryResult.BindUFunction(this, "GetUserInventoryReply");
    OnUserInventoryApiError.BindUFunction(this, "GetUserInventoryError");

    OnConsumeInstanceResult.BindUFunction(this, "GetConsumeInstanceReply");
    OnConsumeInstanceApiError.BindUFunction(this, "GetConsumeInstancetError");

    OnConsumeUserInventoryResult.BindUFunction(this, "GetConsumeUserInventoryReply");
    OnConsumeUserInventoryApiError.BindUFunction(this, "GetConsumeUserInventoryError");

    OnGrantInstanceToUserResult.BindUFunction(this, "GetGrantInstanceToUserReply");
    OnGrantInstanceToUserError.BindUFunction(this, "GetGrantInstanceToUserApiError");

    OnUserAccountInfoResult.BindUFunction(this, "GetUserAccountInfoReply");
    OnUserAccountInfoApiError.BindUFunction(this, "GetUserAccountInfoError");

    Super::NativeConstruct();

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
void UBundleDetailPanel::ShowBundlesDetail(FEconomyBundle itemData)
{
    APIEvents->ShowLoading();
    bundlebases.Empty();
    bundleContents.Empty();
    bundles = itemData;
    virtualCurrrency = itemData.VirtualCurrency;
    bundleContents.Add(itemData.BundleContents);


    for (FContainerBundleContents& BundleContent : bundleContents)
    {
        for (FContainerBase& Bundle : BundleContent.Bundles)
        {
            Bundle.containerType = "BUNDLES";
            bundlebases.Add(Bundle);
            UE_LOG(LogTemp, Display, TEXT("ON LOAD BUNDLES DETAIL DATA--->>%s"), *Bundle.containerType);
        }
    }
    for (FContainerBundleContents& ContainerContent : bundleContents)
    {
        for (FContainerBase& Container : ContainerContent.Container)
        {
            Container.containerType = "CONTAINER";
            bundlebases.Add(Container);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD BUNDLES DETAIL DATA--->>%s"), *Container.containerType);
        }
    }
    for (FContainerBundleContents& CurrencyContent : bundleContents)
    {
        for (FContainerBase& Currency : CurrencyContent.Currencies)
        {
            Currency.containerType = "CURRENCY";
            bundlebases.Add(Currency);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD BUNDLES DETAIL DATA--->>%s"), *Currency.containerType);
        }
    }
    for (FContainerBundleContents& DroptableContent : bundleContents)
    {
        for (FContainerBase& Droptable : DroptableContent.Droptable)
        {
            Droptable.containerType = "DROPTABLE";
            bundlebases.Add(Droptable);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD BUNDLES DETAIL DATA--->>%s"), *Droptable.containerType);
        }
    }
    for (FContainerBundleContents& ItemContent : bundleContents)
    {
        for (FContainerBase& Items : ItemContent.Items)
        {
            Items.containerType = "ITEM";
            bundlebases.Add(Items);
             UE_LOG(LogTemp, Display, TEXT("ON LOAD BUNDLES DETAIL DATA--->>%s"), *Items.containerType);
        }
    }
    if(BundlesDetailItemListView)
    {
        BundlesDetailItemListView->ClearListItems();
    }
   UE_LOG(LogTemp, Display, TEXT("ON Checking Bundles Count--->>%d"), bundlebases.Num());
    for(int i = 0 ; i < bundlebases.Num();i++ )
    {
        UBundlesDetailListData *item = NewObject<UBundlesDetailListData>();
        item->data = bundlebases[i];
        BundlesDetailItemListView->AddItem(item);
    }

}
void UBundleDetailPanel::OnClickBDP_BackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}
void UBundleDetailPanel::BuyBundles()
{
    UE_LOG(LogTemp, Display, TEXT("ON CLICK BUYBUNDLES  --->>%s"), *bundles.DisplayName);

    if(bundles.VirtualCurrency.currencyRewards.Num() > 0 )
    {
        FString vc = bundles.VirtualCurrency.currencyRewards[0].UserID;
        int32 price = FCString::Atoi(*bundles.VirtualCurrency.currencyRewards[0].Amount);

        FPurchaseInstanceRequest request;
       
        request.InstanceID = bundles.ID;
        request.InstanceType = "BUNDLE" ;
        request.Price = price ;
        request.VirtualCurrency =  vc;
    
        APIEvents->ShowLoading();
        UUserItemManagementHandler::PurchaseInstance(request, OnPurchaseInstanceResult,OnPurchaseInstanceApiError);

    }
}
void UBundleDetailPanel::GetPurchaseInstanceReply(FString result)
{
    UE_LOG(LogTemp, Display, TEXT(" BUY Purchase REPY  --->>%s"), *result);
    // APIEvents->HideLoading();
    UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnUserInventoryResult, OnUserInventoryApiError);

}
void UBundleDetailPanel::GetPurchaseInstanceError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT(" BUY Purchase ERROR  --->>%s"), *error.ErrorMessage);
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
}
 void UBundleDetailPanel::GetUserInventoryReply(FGetUserInventoryResult result)
{
    // APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("  GET INVENTORY REPLY  --->>%s"), *result.Status);
    UserInventoryHolder->AddUserInventory(result.Data);
    FGetUserInventoryResultDataInner resultDataInner;
   
    for (const auto& item : UserInventoryHolder->GetInventoryList())
    {
        if (item.InstanceID == bundles.ID && item.Count > 0)
        {
            resultDataInner = item;
            UE_LOG(LogTemp, Display, TEXT("  GOT THE  INVENTORY ITEM  --->>%s"), *item.DisplayName);
            break;
        }
    } 
    FConsumeInstanceRequest request;
    // request.UserID = resultDataInner.UserID;
    request.InstanceID = resultDataInner.ID;
    request.InstanceCount = 1;

    UUserItemManagementHandler::ConsumeInstance(request,OnConsumeInstanceResult,OnConsumeInstanceApiError);

}

void UBundleDetailPanel::GetUserInventoryError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("  GET INVENTORY ERROR  --->>%s"), *error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
}
void UBundleDetailPanel::GetConsumeUserInventoryReply(FGetUserInventoryResult result)
{
    //   APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("  CONSUME INVENTORY REPLY  --->>%s"), *result.Status);
    UserInventoryHolder->AddUserInventory(result.Data);
     UUserAccountManagementAPI::GetUserAccountInfo(UserDetailHolder->UserDetails.userID, OnUserAccountInfoResult, OnUserAccountInfoApiError);
}
void UBundleDetailPanel::GetConsumeUserInventoryError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("  CONSUME INVENTORY ERROR  --->>%s"), *error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
}

void UBundleDetailPanel::GetConsumeInstanceReply(FConsumeInstanceResult result)
{
    // APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE CONSUME -->>%s"),*result.Message);

    TArray<FGrantInstanceToUserRequestInstanceIDsInner> InstanceIDers;

    for(int i = 0 ; i<bundles.BundleContents.Items.Num();i++ )
    {
        FGrantInstanceToUserRequestInstanceIDsInner Instance; 
        Instance.InstanceID = bundles.BundleContents.Items[i].UserID;
        Instance.InstanceType = "ITEM";
        Instance.Quantity = FCString::Atoi(*bundles.BundleContents.Items[i].Quantity);
        InstanceIDers.Add(Instance);
    }
    for(int i = 0 ; i<bundles.BundleContents.Bundles.Num();i++ )
    {
        FGrantInstanceToUserRequestInstanceIDsInner Instance; 
        Instance.InstanceID = bundles.BundleContents.Bundles[i].UserID;
        Instance.InstanceType = "BUNDLES";
        Instance.Quantity = FCString::Atoi(*bundles.BundleContents.Bundles[i].Quantity);
        InstanceIDers.Add(Instance);
    }
    for(int i = 0 ; i<bundles.BundleContents.Container.Num();i++ )
    {
        FGrantInstanceToUserRequestInstanceIDsInner Instance; 
        Instance.InstanceID = bundles.BundleContents.Container[i].UserID;
        Instance.InstanceType = "CONTAINER";
        Instance.Quantity = FCString::Atoi(*bundles.BundleContents.Container[i].Quantity);
        InstanceIDers.Add(Instance);
    }
    for(int i = 0 ; i<bundles.BundleContents.Currencies.Num();i++ )
    {
        FGrantInstanceToUserRequestInstanceIDsInner Instance; 
        Instance.InstanceID = bundles.BundleContents.Currencies[i].UserID;
        Instance.InstanceType = "CURRENCY";
        Instance.Quantity = FCString::Atoi(*bundles.BundleContents.Currencies[i].Quantity);
        InstanceIDers.Add(Instance);
    }

    FGrantInstanceToUserRequest request;
    request.InstanceIDs = InstanceIDers;

    UUserItemManagementHandler::GrantInstanceToUser(request,OnGrantInstanceToUserResult,OnGrantInstanceToUserError);
}
void UBundleDetailPanel::GetConsumeInstancetError(FApiException error)
{
      UE_LOG(LogTemp, Display, TEXT("THE CONSUME ERROR-->>%s"),*error.ErrorMessage);
}
void UBundleDetailPanel::GetGrantInstanceToUserReply(FGrantInstanceToUserResult result)
{
    
    UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER SUCCESS-->>%s"),*result.Message);
      UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnConsumeUserInventoryResult, OnConsumeUserInventoryApiError);
  
}
void UBundleDetailPanel::GetGrantInstanceToUserApiError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER ERROR-->>%s"),*error.ErrorMessage);
}
void UBundleDetailPanel::GetUserAccountInfoReply(FGetUserAccountInfoResult result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info -->>%s"),*result.Status);
    APIEvents->ShowErrorNotification(FString::FromInt(result.Code),"BUNDLES PURCHASED ");
    // this->SetVisibility(ESlateVisibility::Hidden);
}
void UBundleDetailPanel::GetUserAccountInfoError(FApiException error)
{
      APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info  Erroe -->>%s"),*error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
   
}