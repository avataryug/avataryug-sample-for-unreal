// Fill out your copyright notice in the Description page of Project Settings.


#include "AdsPanel.h"
#include "JsonObjectConverter.h"

void UAdsPanel::NativeConstruct()
{
    Super::NativeConstruct();  

    AP_BackButton->OnClicked.RemoveDynamic(this, &UAdsPanel::OnclickAP_BackButton);
    AP_BackButton->OnClicked.AddDynamic(this, &UAdsPanel::OnclickAP_BackButton);

    OnGetAdsPlacementResponse.BindUFunction(this, "GetAdsPlacementReply");
    OnGetAdsPlacementApiError.BindUFunction(this, "GetAdsPlacementError");

    OnRewardItemClick.BindUFunction(this, "OnClickRewardsItemButton");

    OnRecordAdsActivityResponse.BindUFunction(this, "GetRecordAdsActivityReply");
    OnRecordAdsActivityApiError.BindUFunction(this, "GetRecordAdsActivityError");

    OnGrantAdsRewardResponse.BindUFunction(this, "GetGrantAdsRewardReply");
    OnGrantAdsRewardApiError.BindUFunction(this, "GetGrantAdsRewardError");

    OnUserInventoryResult.BindUFunction(this, "GetUserInventoryReply");
    OnUserInventoryApiError.BindUFunction(this, "GetUserInventoryError");

    OnUserAccountInfoResult.BindUFunction(this, "GetUserAccountInfoReply");
    OnUserAccountInfoApiError.BindUFunction(this, "GetUserAccountInfoError");

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
void UAdsPanel::OnclickAP_BackButton()
{
  this->SetVisibility(ESlateVisibility::Hidden);
}
void UAdsPanel::LoadRewardedData()
{
    if (getAdsPlacements.Num() <= 0)
    {
        for (auto& item : AdsIDs)
        {
            quelist.Add(item);
        }
        OnQueData();
    }
}
void UAdsPanel::OnQueData()
{
    if(quelist.Num() > 0)
    {
        FString id = quelist[0];
        quelist.RemoveAt(0);
        GetAdsPlacement(id);
    }
}
void UAdsPanel::GetAdsPlacement(FString id)
{
    APIEvents->ShowLoading();
    UDefaultHandler::GetAdsPlacement(id, OnGetAdsPlacementResponse, OnGetAdsPlacementApiError);
}
void UAdsPanel::GetAdsPlacementReply(FGetAdsPlacementResponse result)
{
    UE_LOG(LogTemp, Display, TEXT("Rewarded Success--STATUS-->>%s"),*result.Status);
   

    FAdsPlacementClass rewards;

    rewards.PlacementName = result.Data.PlacementName;
    // rewards.AppId = result.Data.ID;
    rewards.AdUnit = result.Data.AdUnit;
    rewards.Segments = result.Data.Segments;
    rewards.Status = result.Data.Status;
    rewards.ID = result.Data.ID;

    FString currencystr = "{\"adsRewards\":";
    currencystr.Append(result.Data.Rewards);
    currencystr.Append("}");
    // rewards.Rewards;
    FAdsRewards currneyrew;
    FJsonObjectConverter::JsonObjectStringToUStruct(currencystr, &currneyrew,0,0);
    rewards.Rewards = currneyrew;

    FString adsLimitstr = "{\"adsLimits\":";
    adsLimitstr.Append(result.Data.AdLimits);
    adsLimitstr.Append("}");
    FAdsLimit adsLimitnew;
    FJsonObjectConverter::JsonObjectStringToUStruct(adsLimitstr, &adsLimitnew,0,0);
    rewards.AdLimits = adsLimitnew;

    getAdsPlacements.Add(rewards);
    OnQueData();
    ShowRewardDataAfterLoad();
    UE_LOG(LogTemp, Display, TEXT("ADDED---Rewarded COUNT---->>%d"),getAdsPlacements.Num());

}
void UAdsPanel::GetAdsPlacementError(FApiException result)
{
    UE_LOG(LogTemp, Display, TEXT("ADDED---Rewarded Error---->>%s"),*result.ErrorMessage);
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),result.ErrorMessage);
}
void UAdsPanel::ShowRewardDataAfterLoad()
{
    UE_LOG(LogTemp, Display, TEXT("Show Reward Data AfterLoad ---->>"));

    if(RewardAdsItemListView) 
    {
        RewardAdsItemListView->ClearListItems();
    }

    int floatValue = getAdsPlacements.Num();
    float contaientGridCount = floatValue / 2;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UAdsListData *item = NewObject<UAdsListData>();
        item->StartIndex = 2 * i;
        item->TotalCount = getAdsPlacements.Num();
        item->rewardItem = getAdsPlacements;
        item->callback = OnRewardItemClick;
        RewardAdsItemListView->AddItem(item);
    }
    if(myCeilInt == 1 )
    {
    // UE_LOG(LogTemp, Display, TEXT("Show Reward Data AfterLoad ---->>%d"),myCeilInt);
    APIEvents->HideLoading();
    }
}

void UAdsPanel::OnClickRewardsItemButton(FAdsPlacementClass item)
{
    UE_LOG(LogTemp, Display, TEXT("OnClickRewardsItemButton-->>  %s"), *item.ID);
    APIEvents->ShowLoading();
    FRecordAdsActivityRequest request;
    request.AdRevenue = 1;
    request.PlacementID = item.ID;
    request.RevenueCurrency = "RM";
    currentItem = item;
    UDefaultHandler::RecordAdsActivity(request,OnRecordAdsActivityResponse,OnRecordAdsActivityApiError);

}
void UAdsPanel::GetRecordAdsActivityReply(FRecordAdsActivityResponse result)
{
     UE_LOG(LogTemp, Display, TEXT("RecordActivity ---->>%s"),*result.Status);
       UE_LOG(LogTemp, Display, TEXT("RecordActivity --IDD-->>%s"),*currentItem.ID);
     FGrantAdsRewardRequest request ;
     request.PlacementID = currentItem.ID;
     UDefaultHandler::GrantAdsReward(request,OnGrantAdsRewardResponse,OnGrantAdsRewardApiError);
}
void UAdsPanel::GetRecordAdsActivityError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("RecordActivity Error---->>%s"),*result.ErrorMessage);
}
void UAdsPanel::GetGrantAdsRewardReply(FGrantAdsRewardResponse result)
{
    UE_LOG(LogTemp, Display, TEXT("GrantAds---Reward ---->>%s"),*result.Status);
    UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnUserInventoryResult, OnUserInventoryApiError);
}
void UAdsPanel::GetGrantAdsRewardError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GrantAds---Reward --ERROR-->>%s"),*result.ErrorMessage);
     APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),"NO REWARD FOUND ");
}
void UAdsPanel::GetUserInventoryReply(FGetUserInventoryResult result)
{
    UE_LOG(LogTemp, Display, TEXT("  GET INVENTORY REPLY  --->>%s"), *result.Status);
    UserInventoryHolder->AddUserInventory(result.Data);
    UUserAccountManagementAPI::GetUserAccountInfo(UserDetailHolder->UserDetails.userID, OnUserAccountInfoResult, OnUserAccountInfoApiError);
}
void UAdsPanel::GetUserInventoryError(FApiException error)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("THE INVENTORY ERROR-->>%s"),*error.ErrorMessage);
}
void UAdsPanel::GetUserAccountInfoReply(FGetUserAccountInfoResult result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info -->>%s"),*result.Status);
    APIEvents->ShowErrorNotification(FString::FromInt(result.Code),"REWARD GRANTED ");
    // this->SetVisibility(ESlateVisibility::Hidden);
}
void UAdsPanel::GetUserAccountInfoError(FApiException error)
{
      APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("GET Account Info  Erroe -->>%s"),*error.ErrorMessage);
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
   
}