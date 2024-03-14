// Fill out your copyright notice in the Description page of Project Settings.


#include "BundleDetailButton.h"


void UBundleDetailButton::NativeConstruct()
{
    Super::NativeConstruct();

    OnGetEconomyItemsByIDResult.BindUFunction(this,"GetEconomyItemsByIDReply");
    OnGetEconomyItemsByIDError.BindUFunction(this,"GetEconomyItemsByIDApiError");

    OnGetEconomyBundleByIDResult.BindUFunction(this,"GetEconomyBundleByIDReply");
    OnGetEconomyBundleByIDError.BindUFunction(this,"GetEconomyBundleByIDApiError");

    OnGetEconomyContainerByIDResult.BindUFunction(this,"GetEconomyContainerByIDReply");
    OnGetEconomyContainerByIDError.BindUFunction(this,"GetEconomyContainerByIDApiError");

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
}
void UBundleDetailButton:: NativeOnListItemObjectSet(UObject* ListItemObject)
{
     auto* item = Cast<UBundlesDetailListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
        APIEvents->HideLoading();
		return;
	}
    if (item->data.containerType == "BUNDLES") 
    {
        SetBundlesDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE BUNDLE"));
    } 
    else if (item->data.containerType == "CONTAINER") 
    {
        SetContainerDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE CONTAINER"));
    }
    else if (item->data.containerType == "CURRENCIES") 
    {
        SetCurrenciesDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE CURRENCIES"));
    } 
    else if (item->data.containerType == "CURRENCY") 
    {
        SetCurrenciesDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE CURRENCY"));
    } 
    else if (item->data.containerType == "DROPTABLE") 
    {
        SetDroptableDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE DROPTABLE"));
    }  
    else if (item->data.containerType == "ITEM") 
    {
        SetItemDetail(item->data);
        UE_LOG(LogTemp, Display, TEXT("GOT THE ITEM"));
    }
    else if (item->data.containerType == "") 
    {
            APIEvents->HideLoading();
        UE_LOG(LogTemp, Display, TEXT("GOT THE EMPTYDATA TYPE%s---->>"),*item->data.containerType); 
       
    }
    else 
    {
            APIEvents->HideLoading();
        UE_LOG(LogTemp, Display, TEXT("GOT THE UNKNOW")); 
    } 
}
void UBundleDetailButton:: SetBundlesDetail(FContainerBase data)
{
    UEconomyHandler::GetEconomyBundleByID(data.UserID,OnGetEconomyBundleByIDResult,OnGetEconomyBundleByIDError);
}
void UBundleDetailButton:: SetContainerDetail(FContainerBase data)
{
    APIEvents->ShowLoading();
    UEconomyHandler::GetEconomyContainerByID(data.UserID,OnGetEconomyContainerByIDResult,OnGetEconomyContainerByIDError);
}
void UBundleDetailButton:: SetCurrenciesDetail(FContainerBase data)
{
    BDI_PriceText->SetText(FText::FromString(data.Quantity + " " +  data.Code));     
    APIEvents->HideLoading();
}
void UBundleDetailButton:: SetDroptableDetail(FContainerBase data)
{
        APIEvents->HideLoading();
}
void UBundleDetailButton:: SetItemDetail(FContainerBase data)
{
    if(EconomyItemHolder->IsEconomyItemPresent(data.UserID))
    {  
        UE_LOG(LogTemp, Display, TEXT("IS PERESENT IN ECONOMY ITEMS"));
        FString tex = EconomyItemHolder->GetEconomyItemWithId(data.UserID).displayName;
        BDI_PriceText->SetText(FText::FromString(tex)); 
        APIEvents->HideLoading();
    }
    else
    {
        APIEvents->ShowLoading();
        UEconomyHandler::GetEconomyItemsByID(data.UserID,OnGetEconomyItemsByIDResult,OnGetEconomyItemsByIDError);
    }
}
void UBundleDetailButton::GetEconomyItemsByIDReply(FGetEconomyItemsByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY SUCCESS--->>%s"), *result.Status);
    // economyItemsList.Add(result.Data);
    BDI_PriceText->SetText(FText::FromString(result.Data.DisplayName));   
     APIEvents->HideLoading();
}
void UBundleDetailButton::GetEconomyItemsByIDApiError(FApiException error)
{
     APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"), *error.ErrorMessage);
}
void UBundleDetailButton:: GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID SUCCESS--->>%s"), *result.Status);
    BDI_PriceText->SetText(FText::FromString(result.Data.DisplayName));  
     APIEvents->HideLoading(); 
}
void UBundleDetailButton::GetEconomyBundleByIDApiError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID--->>%s"), *error.ErrorMessage);
     APIEvents->HideLoading();
}
void UBundleDetailButton::GetEconomyContainerByIDReply(FGetEconomyContainerByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET Container==BY==ID SUCCESS--->>%s"), *result.Status);
    BDI_PriceText->SetText(FText::FromString(result.Data.DisplayName)); 
     APIEvents->HideLoading();
}
void UBundleDetailButton::GetEconomyContainerByIDApiError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET Container==BY==ID--->>%s"), *error.ErrorMessage);   
     APIEvents->HideLoading();
}