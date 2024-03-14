// Fill out your copyright notice in the Description page of Project Settings.
#include "StorePanel.h"
#include "JsonUtilities.h"
#include "JsonObjectConverter.h"
#include "Json.h"
#include "CoreUObject.h"
#include "Kismet/GameplayStatics.h"
#include "Core.h"
#include "Engine.h"
#include "StorePanelButton.h"

void UStorePanel::NativeConstruct()
{
    Super::NativeConstruct();  

    CurrencyStore_BackButton->OnClicked.RemoveDynamic(this, &UStorePanel::OnClickStoreBackButton);
    CurrencyStore_BackButton->OnClicked.AddDynamic(this, &UStorePanel::OnClickStoreBackButton);

    GetEconomyBundleByIDResult.BindUFunction(this,"GetEconomyBundleByIDReply");
    GetEconomyBundleByIDApiError.BindUFunction(this,"GetEconomyBundleByIDError");

    OnPurchaseInstanceResult.BindUFunction(this,"GetPurchaseInstanceReply");
    OnPurchaseInstanceApiError.BindUFunction(this,"GetPurchaseInstanceError");

    OnGetUserInventoryResult.BindUFunction(this,"GetUserInventoryResult");
    OnInventoryApiError.BindUFunction(this,"InventoryApiError");

    OnConsumeInstanceResult.BindUFunction(this,"OnConsumeInstanceReply");
    OnConsumeInstanceError.BindUFunction(this,"OnConsumeInstancetApiError");

    OnGrantInstanceToUserResult.BindUFunction(this,"OnGrantInstanceToUserReply");
    OnGrantInstanceToUserError.BindUFunction(this,"OnGrantInstanceToUserApiError");
 

//    SelectedIndexReceived.RemoveDynamic(this, &UStorePanel::PurchaseItem);
    SelectedIndexReceived.AddDynamic(this, &UStorePanel::PurchaseItem);

    if (UserDetailHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserDetailHolder::StaticClass());
        UserDetailHolder = Cast<AUserDetailHolder>(FoundActor);
        if (UserDetailHolder == nullptr)
        {
            UserDetailHolder = GetWorld()->SpawnActor<AUserDetailHolder>();
        }
    }
    if(CommonFunction == nullptr){
         AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
  CommonFunction = Cast<ACommonFunction>(FoundActor);
  if (CommonFunction == nullptr)
  {
    CommonFunction = GetWorld()->SpawnActor<ACommonFunction>();
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
}

void UStorePanel::OnClickStoreBackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
}


void UStorePanel::StorePanelData()
{
  APIEvents->ShowLoading();
    if (Currencies.Num() > 0)
    {
        LoadCurrencyData();
    }
    else
    {
        UEconomyHandler::GetStoreItemsByID("21dc0fd4-6945-4bc6-bda3-c0ace7edee1d",[this](FGetStoreItemsByIDResult result) 
        {
           
            getEconomyStore = result;
            FStoreContents storeContnets;
            FString ResponseString = "{";
            ResponseString.Append("\"storecontent\":");
            ResponseString.Append(getEconomyStore.Data.StoreContents); 
            ResponseString.Append("}"); 
            FJsonObjectConverter::JsonObjectStringToUStruct(ResponseString, &storeContnets,0,0);
            storecontents = storeContnets;
            Currencies.Empty();
            QueueList.Empty();
            bundleContents.Empty();
            for (int i = 0; i < storecontents.storecontent.Num(); i++)
            {
                QueueList.Add(storecontents.storecontent[i]);
            }
            OnQueueData();
        },
        [this](FApiException error)
        {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
        });
    }
}

void UStorePanel::OnQueueData()
{
    if(QueueList.Num() > 0)
    {
        FStoreContent data = QueueList[0];
        LoadStoreItemDetail(data,storecontents.storecontent.Num() - QueueList.Num());
        QueueList.RemoveAt(0);
    }
    else
    {
        LoadCurrencyData();
    }
}
void UStorePanel::LoadStoreItemDetail(FStoreContent data,int32 index)
{
    if(data.Type == "Bundles")
    {
        UEconomyHandler::GetEconomyBundleByID(data.UserID,GetEconomyBundleByIDResult,GetEconomyBundleByIDApiError);
    }
}

void UStorePanel::GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result)
{
    FMyBundleContents myBundleContents;
    FJsonObjectConverter::JsonObjectStringToUStruct<FMyBundleContents>(result.Data.BundleContents, &myBundleContents, 0, 0);
    bundleContents.Add(myBundleContents);
    OnQueueData();
}
void UStorePanel::GetEconomyBundleByIDError(FApiException result)
{
      UE_LOG(LogTemp, Display, TEXT("BUNDLESS DATA--->>Error%s"),*result.ErrorMessage);
}

void UStorePanel:: LoadCurrencyData()
{
    if (Currencies.Num() <=0)
    {
        for(int i = 0 ; i < bundleContents.Num();i++)
        {
            for(int k = 0; k < bundleContents[i].Currencies.Num();k++)
            {
                Currencies.Add(bundleContents[i].Currencies[k]);
            }
        }
    }

    UE_LOG(LogTemp, Display, TEXT("THE  CURRENCYITEMS--COUNTS-->>%d"),Currencies.Num());
    
    if (CurrencyItemListView)
    {
        CurrencyItemListView->ClearListItems();
    }
      
    for (int i = 0; i < Currencies.Num(); i++)
    {
        UStoreListData *item = NewObject<UStoreListData>();
        item->currentItem = Currencies[i];
        item->Index = i;
        item->StoreIndexReceived = SelectedIndexReceived;
        CurrencyItemListView->AddItem(item);
    }
     APIEvents->HideLoading();
}
void UStorePanel::PurchaseItem(int32 index)
{
    indexRedceived = index;
    UE_LOG(LogTemp, Display, TEXT("SelectedIndex: %d"), index);
    FStoreContent storeContent = storecontents.storecontent[index];
    newstoreContent = storecontents.storecontent[index];
    int32 amount = 0 ;
    FString code = "";
     APIEvents->ShowLoading();

    if(storeContent.VirtualCurrency.Num() > 0)
    {
        // UE_LOG(LogTemp, Display, TEXT("THE Amountt -->>%s"),*storeContent.VirtualCurrency[0].UserID);
        amount = FCString::Atoi(*storeContent.VirtualCurrency[0].Amount);
        code = storeContent.VirtualCurrency[0].UserID;
        
    }

    UE_LOG(LogTemp, Display, TEXT("THE Amountt SUCCESS-->>%s"),*storeContent.DisplayName);

    FPurchaseInstanceRequest request;
    // request.UserID = UserDetailHolder->UserDetails.userID;
    request.VirtualCurrency= code;
    request.Price= amount;
    request.InstanceType="BUNDLE";
    request.StoreID=StoreID;
    request.InstanceID=storeContent.UserID;

    UUserItemManagementHandler::PurchaseInstance(request,OnPurchaseInstanceResult,OnPurchaseInstanceApiError);

}
void UStorePanel::GetPurchaseInstanceReply(FString result)
{
     UE_LOG(LogTemp, Display, TEXT("THE PURCHASE SUCCESS-->>%s"),*result);
      UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
}
void UStorePanel::GetPurchaseInstanceError(FApiException result)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(result.ErrorCode),result.ErrorMessage);
      UE_LOG(LogTemp, Display, TEXT("THE PURCHASE ERROR-->>%s"),*result.ErrorMessage);
}
void UStorePanel::GetUserInventoryResult(FGetUserInventoryResult result)
{

    UserInventoryHolder->AddUserInventory(result.Data);
    UE_LOG(LogTemp, Display, TEXT("Store Invetroy Call------>>%s"),*result.Status);
    ConsumeInstance(newstoreContent,FCString::Atoi(*Currencies[indexRedceived].Quantity),Currencies[indexRedceived].UserID);



    //   FString userid = UserDetailHolder->UserDetails.userID;
    


     
}
void UStorePanel::ConsumeInstance(FStoreContent content, int32 qut , FString id)
{
    // UserInventoryHolder->Inventory
     FConsumeInstanceRequest request;
     bool isfound = false;
    for (const auto& inventoryItem : UserInventoryHolder->Inventory)
    {
        if (inventoryItem.InstanceID == content.UserID && inventoryItem.Count > 0)
        {
            // Do something with the matching inventory item
            request.InstanceID = inventoryItem.ID;
            request.InstanceCount = 1;
            isfound = true;
        }
    }
    if(isfound)
    {
        UUserItemManagementHandler::ConsumeInstance(request,OnConsumeInstanceResult,OnConsumeInstanceError);
    }
}
void UStorePanel::OnConsumeInstanceReply(FConsumeInstanceResult result)
{
    
    UE_LOG(LogTemp, Display, TEXT("THE CONSUME SUCCESS-->>%s"),*result.Message);
    FGrantInstanceToUserRequest request;

    TArray<FGrantInstanceToUserRequestInstanceIDsInner> InstanceIDers;
    FGrantInstanceToUserRequestInstanceIDsInner InstanceToUserRequestInstanceIDsInner ;
    InstanceToUserRequestInstanceIDsInner.InstanceID = Currencies[indexRedceived].UserID;
    InstanceToUserRequestInstanceIDsInner.InstanceType = "CURRENCY" ;
    InstanceToUserRequestInstanceIDsInner.Quantity = FCString::Atoi(*Currencies[indexRedceived].Quantity);
    InstanceIDers.Add(InstanceToUserRequestInstanceIDsInner);
    request.InstanceIDs = InstanceIDers;


    UUserItemManagementHandler::GrantInstanceToUser(request,OnGrantInstanceToUserResult,OnGrantInstanceToUserError);
    
}
void UStorePanel::OnConsumeInstancetApiError(FApiException error)
{
     APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
    UE_LOG(LogTemp, Display, TEXT("THE CONSUME ERROR-->>%s"),*error.ErrorMessage);
}
void UStorePanel::InventoryApiError(FApiException error)
{
    APIEvents->HideLoading();
    APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode),error.ErrorMessage);
    UE_LOG(LogTemp, Display, TEXT("Store Invetroy Call------>>Error%s"),*error.ErrorMessage);
}
void UStorePanel::OnGrantInstanceToUserReply(FGrantInstanceToUserResult result)
{
    
    UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER SUCCESS-->>%s"),
           *result.Message);
    CommonFunction->GetUserAccountInfo(
        [this, result](FGetUserAccountInfoResult info) {
          APIEvents->HideLoading();
          APIEvents->ShowErrorNotification(FString::FromInt(result.Code), Currencies[indexRedceived].Quantity +  " Coins Added" );
        });
    
}
void UStorePanel::OnGrantInstanceToUserApiError(FApiException error)
{
    APIEvents->HideLoading();
      UE_LOG(LogTemp, Display, TEXT(" GRANT TO USER ERROR-->>%s"),*error.ErrorMessage);
}