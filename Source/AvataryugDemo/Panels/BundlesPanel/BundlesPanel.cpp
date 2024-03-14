// Fill out your copyright notice in the Description page of Project Settings.

#include "BundlesPanel.h"

#include "JsonObjectConverter.h"
#include "BundleButtonGrid.h"
#include "Components/ListView.h"
#include "EconomyAPI/EconomyHandler.h"

void UBundlesPanel::NativeConstruct()
{
    Super::NativeConstruct();

    GetEconomyBundlesResult.BindUFunction(this, "GetEconomyBundlesReply");
    GetEconomyBundlesApiError.BindUFunction(this, "GetEconomyBundlesError");

    Bundles_BackButton->OnClicked.RemoveDynamic(this, &UBundlesPanel::OnClickBundles_BackButton);
    Bundles_BackButton->OnClicked.AddDynamic(this, &UBundlesPanel::OnClickBundles_BackButton);
    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
    // LoadBundlePanelData();
}

void UBundlesPanel::LoadBundlePanelData()
{
    APIEvents->ShowLoading();
    if (m_EconomyBundles.Num() <= 0)
    {
        UEconomyHandler::GetEconomyBundles(1, GetEconomyBundlesResult, GetEconomyBundlesApiError);
    }
    else
    {
        ShowDataAfterLoad();
    }
}
void UBundlesPanel::GetEconomyBundlesReply(FGetEconomyBundlesResult result)
{
    UE_LOG(LogTemp, Display, TEXT("BUNDLES Success--STATUS-->>%s"), *result.Status);
    AddBundles(result);
    ShowDataAfterLoad();
}
void UBundlesPanel::GetEconomyBundlesError(FApiException result)
{
    APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("BUNDLES ------>>Error%s"), *result.ErrorMessage);
}
bool UBundlesPanel::IsBundlePresent(FString id)
{
    bool isPresent = false;
    for (int i = 0; i < m_EconomyBundles.Num(); i++)
    {
        if (m_EconomyBundles[i].ID == id)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}
void UBundlesPanel::AddBundles(FGetEconomyBundlesResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ADDED---BUNDLES Success---->>%d"), result.Data.Num());
    for (int i = 0; i < result.Data.Num(); i++)
    {
        if (!IsBundlePresent(result.Data[i].ID))
        {
            FEconomyBundle bundle;
            bundle.ID = result.Data[i].ID;
            bundle.BundleCategory = result.Data[i].BundleCategory;
            bundle.DisplayName = result.Data[i].DisplayName;
            bundle.Description = result.Data[i].Description;
            bundle.RealCurrency = result.Data[i].RealCurrency;
            bundle.Tags = result.Data[i].Tags;
            bundle.IsStackable = result.Data[i].IsStackable;
            bundle.BundleImageUrl = result.Data[i].BundleImageUrl;
            bundle.IsLimitedEdition = result.Data[i].IsLimitedEdition;
            bundle.LimitedEditionIntialCount = result.Data[i].LimitedEditionIntialCount;
            bundle.CustomMetaData = result.Data[i].CustomMetaData;

            FContainerBundleContents conte;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].BundleContents, &conte,0,0);
            bundle.BundleContents = conte;

            bundle.Status = result.Data[i].Status;

            FEntitlements entitlements;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].Entitlement, &entitlements,0,0);

            FString currencystr = "{\"currencyRewards\":";
            currencystr.Append(result.Data[i].VirtualCurrency);
            currencystr.Append("}");
            // bundle.VirtualCurrency;
            FVirtualCurrencyReward currneyrew;
            FJsonObjectConverter::JsonObjectStringToUStruct(currencystr, &currneyrew,0,0);
            bundle.VirtualCurrency = currneyrew;

            m_EconomyBundles.Add(bundle);
        }
    }
}
void UBundlesPanel::ShowDataAfterLoad()
{
    UE_LOG(LogTemp, Display, TEXT("SHOW---ADDED---BUNDLES ---->>"));
    APIEvents->HideLoading();
    if (BundlesItemListView)
    {
        BundlesItemListView->ClearListItems();
    }

    float floatValue = m_EconomyBundles.Num();
    float contaientGridCount = floatValue / 2;
    int myCeilInt = FMath::CeilToInt(contaientGridCount);
    for (int i = 0; i < myCeilInt; i++)
    {
        UBundleListData *item = NewObject<UBundleListData>();
        item->StartIndex = 2 * i;
        item->TotalCount = m_EconomyBundles.Num();
        item->bundleItem = m_EconomyBundles;
        item->panel = BP_BundlesDetailPanel;
        BundlesItemListView->AddItem(item);
    }
}
void UBundlesPanel::OnClickBundles_BackButton()
{
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::HOME, true);
}