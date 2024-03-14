// Fill out your copyright notice in the Description page of Project Settings.
#include "ContainersPanel.h"
#include "EconomyAPI/EconomyRequest.h"
#include "Kismet/GameplayStatics.h"
#include "EconomyAPI/EconomyHandler.h"
#include "JsonObjectConverter.h"
#include "ContainerButtonGrid.h"
#include "Components/ListView.h"
#include "ContainersData.h"
void UContainersPanel::NativeConstruct()
{
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

    GetEconomyContainersResult.BindUFunction(this, "GetEconomyContainersReply");
    GetEconomyContainersApiError.BindUFunction(this, "GetEconomyContainersError");

    CP_BackButton->OnClicked.RemoveDynamic(this, &UContainersPanel::OnClickBackButton);
    CP_BackButton->OnClicked.AddDynamic(this, &UContainersPanel::OnClickBackButton);

    // LoadContainerPanelData();
}

void UContainersPanel::OnClickBackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::HOME, true);
}

void UContainersPanel::LoadContainerPanelData()
{
    if (Containers.Num() <= 0)
    {
        UEconomyHandler::GetEconomyContainers(1,GetEconomyContainersResult, GetEconomyContainersApiError);
    }
    else
    {
        ShowDataAfterLoad();
    }
}

void UContainersPanel::GetEconomyContainersReply(FGetEconomyContainersResult result)
{
    AddContainers(result);
    ShowDataAfterLoad();
}
void UContainersPanel::GetEconomyContainersError(FApiException result)
{
    UE_LOG(LogTemp, Display, TEXT("Container ------>>Error%s"), *result.ErrorMessage);
}

void UContainersPanel::AddContainers(FGetEconomyContainersResult result)
{
    Containers.Empty();
    for (int i = 0; i < result.Data.Num(); i++)
    {
        if (!IsContainerPresent(result.Data[i].ID))
        {
            FContainerDataClass item;
            item.Status = result.Data[i].Status;
            item.DisplayName = result.Data[i].DisplayName;
            item.ContainerCategory = result.Data[i].ContainerCategory;
            item.Description = result.Data[i].Description;
            item.Tags = result.Data[i].Tags;
            item.ContainerImageUrl = result.Data[i].ContainerImageUrl;
            item.IsStackable = result.Data[i].IsStackable;
            item.IsLimitedEdition = result.Data[i].IsLimitedEdition;
            item.LimitedEditionIntialCount = result.Data[i].LimitedEditionIntialCount;
            item.Entitlement = result.Data[i].Entitlement;
            item.RealCurrency = result.Data[i].RealCurrency;
            item.CustomMetaData = result.Data[i].CustomMetaData;
            item.ID = result.Data[i].ID;

            FContainerSetting setting;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].ContainerSettings, &setting,0,0);
            item.containerSettings = setting;

            FContainerBundleContents contents;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].ContainerContents, &contents,0,0);
            item.containerContents = contents;

            FString currencystr = "{\"currencyRewards\":";
            currencystr.Append(result.Data[i].VirtualCurrency);
            currencystr.Append("}");
            // item.VirtualCurrency;
            FVirtualCurrencyReward currneyrew;
            FJsonObjectConverter::JsonObjectStringToUStruct(currencystr, &currneyrew,0,0);
            item.VirtualCurrency = currneyrew;

            Containers.Add(item);
        }
    }
}

bool UContainersPanel::IsContainerPresent(FString id)
{
    bool isPresent = false;
    for (int i = 0; i < Containers.Num(); i++)
    {
        if (Containers[i].ID == id)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}

void UContainersPanel::ShowDataAfterLoad()
{
    // ContainerItemListView
    if (ContainerItemListView)
    {
        ContainerItemListView->ClearListItems();
    }
    float floatValue = Containers.Num();
    float contaientGridCount = floatValue / 2;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UContainerListData *item = NewObject<UContainerListData>();
        item->StartIndex = 2 * i;
        item->TotalCount = Containers.Num();
        item->Containers = Containers;
        item->panel = BP_ContainerDetailPanel;
        ContainerItemListView->AddItem(item);
    }
}
