// Fill out your copyright notice in the Description page of Project Settings.


#include "ContainerDetailButton.h"

void UContainerDetailButton::NativeConstruct()
{
    Super::NativeConstruct();

    ContainerDetailItemButton->OnClicked.RemoveDynamic(this,&UContainerDetailButton::OnContainetDetailButtonClick);
    ContainerDetailItemButton->OnClicked.AddDynamic(this,&UContainerDetailButton::OnContainetDetailButtonClick);

    OnGetEconomyItemsByIDResult.BindUFunction(this,"GetEconomyItemsByIDReply");
    OnGetEconomyItemsByIDError.BindUFunction(this,"GetEconomyItemsByIDApiError");

    OnGetEconomyBundleByIDResult.BindUFunction(this,"GetEconomyBundleByIDReply");
    OnGetEconomyBundleByIDError.BindUFunction(this,"GetEconomyBundleByIDApiError");

    OnGetEconomyContainerByIDResult.BindUFunction(this,"GetEconomyContainerByIDReply");
    OnGetEconomyContainerByIDError.BindUFunction(this,"GetEconomyContainerByIDApiError");
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
void UContainerDetailButton:: NativeOnListItemObjectSet(UObject* ListItemObject)
{
     auto* item = Cast<UContainerDetailListData>(ListItemObject);
	if (!item) 
	{
	    UE_LOG(LogTemp, Display, TEXT("Err"));
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
        UE_LOG(LogTemp, Display, TEXT("GOT THE CURRENCIES"));
    } 
    else if (item->data.containerType == "CURRENCY") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE CURRENCY"));
          APIEvents->ShowLoading();
        SetCurrenciesDetail(item->data);
    } 
    else if (item->data.containerType == "DROPTABLE") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE DROPTABLE"));
    } 
    else if (item->data.containerType == "ITEM") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE ITEM"));
        SetItemDetail(item->data);
    } 
    else if (item->data.containerType == "Items") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE Items"));  
        SetItemDetail(item->data);  
    }
    else if (item->data.containerType == "Bundles") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE Bundles")); 
    }
    else if (item->data.containerType == "") 
    {
        UE_LOG(LogTemp, Display, TEXT("GOT THE EMPTYDATA TYPE%s---->>"),*item->data.containerType); 
       
    }
    else 
    {
         UE_LOG(LogTemp, Display, TEXT("GOT THE UNKNOW")); 
    }


   
}
void UContainerDetailButton::OnContainetDetailButtonClick()
{
    UE_LOG(LogTemp, Display, TEXT("ON ContainerDetail BUTTON CLICKED--->>"));
}
void UContainerDetailButton::SetBundlesDetail(FContainerBase data)
{
     APIEvents->ShowLoading();
    UEconomyHandler::GetEconomyBundleByID(data.UserID,OnGetEconomyBundleByIDResult,OnGetEconomyBundleByIDError);
}
void UContainerDetailButton:: SetContainerDetail(FContainerBase data)
{
      APIEvents->ShowLoading();
    UEconomyHandler::GetEconomyContainerByID(data.UserID,OnGetEconomyContainerByIDResult,OnGetEconomyContainerByIDError);
}
void UContainerDetailButton::SetCurrenciesDetail(FContainerBase data)
{
    ContainerDetailItemNameText->SetText(FText::FromString(data.Quantity + " " +  data.Code));     
    APIEvents->HideLoading();
}
void UContainerDetailButton::SetDroptableDetail(FContainerBase data)
{
    
}
void UContainerDetailButton::SetItemDetail(FContainerBase data)
{
    bool isPresent = false;
    if(economyItemsList.Num() > 0 )
    {
        for (FGetEconomyItemsByIDResultData& content : economyItemsList)
        {
            if(content.ID == data.UserID)
            {
                ContainerDetailItemNameText->SetText(FText::FromString(content.DisplayName));   
                 APIEvents->HideLoading();
                isPresent = true;
                break;
            }
        }
    }
    if(!isPresent)
    {
         APIEvents->ShowLoading();
        UEconomyHandler::GetEconomyItemsByID(data.UserID,OnGetEconomyItemsByIDResult,OnGetEconomyItemsByIDError);
    }
}
void UContainerDetailButton::GetEconomyItemsByIDReply(FGetEconomyItemsByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY SUCCESS--->>%s"), *result.Status);
    economyItemsList.Add(result.Data);
    ContainerDetailItemNameText->SetText(FText::FromString(result.Data.DisplayName));   
     APIEvents->HideLoading();
}
void UContainerDetailButton::GetEconomyItemsByIDApiError(FApiException error)
{
     APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"), *error.ErrorMessage);
}
void UContainerDetailButton:: GetEconomyBundleByIDReply(FGetEconomyBundleByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID SUCCESS--->>%s"), *result.Status);
    ContainerDetailItemNameText->SetText(FText::FromString(result.Data.DisplayName));  
     APIEvents->HideLoading(); 
}
void UContainerDetailButton::GetEconomyBundleByIDApiError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET BUNDLES==BY==ID--->>%s"), *error.ErrorMessage);
     APIEvents->HideLoading();
}
void UContainerDetailButton::GetEconomyContainerByIDReply(FGetEconomyContainerByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET Container==BY==ID SUCCESS--->>%s"), *result.Status);
    ContainerDetailItemNameText->SetText(FText::FromString(result.Data.DisplayName)); 
     APIEvents->HideLoading();
}
void UContainerDetailButton::GetEconomyContainerByIDApiError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("ON GET Container==BY==ID--->>%s"), *error.ErrorMessage);   
     APIEvents->HideLoading();
}