// Fill out your copyright notice in the Description page of Project Settings.


#include "AvatarLoaderUI.h"
#include <AuthenticationAPI/AuthenticationModels.h>
#include <AuthenticationAPI/AuthenticationHandler.h>
#include <EconomyAPI/EconomyHandler.h>
#include <EconomyAPI/EconomyModel.h>
#include "Math/UnrealMathUtility.h"
#include <JsonUtilities.h>

void UAvatarLoaderUI::NativeConstruct()
{
	Super::NativeConstruct();

	LoginButton->OnClicked.RemoveDynamic(this, &UAvatarLoaderUI::OnClickLoginButton);
	LoginButton->OnClicked.AddDynamic(this, &UAvatarLoaderUI::OnClickLoginButton);

    TopButton->OnClicked.RemoveDynamic(this, &UAvatarLoaderUI::OnClickTopButton);
    TopButton->OnClicked.AddDynamic(this, &UAvatarLoaderUI::OnClickTopButton);

    BottomButton->OnClicked.RemoveDynamic(this, &UAvatarLoaderUI::OnClickBottomButton);
    BottomButton->OnClicked.AddDynamic(this, &UAvatarLoaderUI::OnClickBottomButton);

    MoreButton->OnClicked.RemoveDynamic(this, &UAvatarLoaderUI::OnClickMoreButton);
    MoreButton->OnClicked.AddDynamic(this, &UAvatarLoaderUI::OnClickMoreButton);

    OkButton->OnClicked.RemoveDynamic(this, &UAvatarLoaderUI::OnClickOkButton);
    OkButton->OnClicked.AddDynamic(this, &UAvatarLoaderUI::OnClickOkButton);

	LoginPanel->SetVisibility(ESlateVisibility::Visible);
	AvatarLoaderPanel->SetVisibility(ESlateVisibility::Hidden);
	LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
    MoreDetailsPanel->SetVisibility(ESlateVisibility::Hidden);

    if (CustomizeAvatarLoader == nullptr)
    {
        AActor* FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACustomizeAvatarLoader::StaticClass());
        CustomizeAvatarLoader = Cast<ACustomizeAvatarLoader>(FoundActor);
    }
}

void UAvatarLoaderUI::OnClickLoginButton()
{
    LoadingPanel->SetVisibility(ESlateVisibility::Visible);
    FLoginWithCustomIDRequest request;
    request.CustomID = "CustomID";
    request.CreateAccount = true;
    UAuthenticationHandler::LoginWithCustomId(request, [this](FLoginWithCustomIDResult result)
    {
        LoadingPanel->SetVisibility(ESlateVisibility::Hidden);
        LoginPanel->SetVisibility(ESlateVisibility::Hidden);
        AvatarLoaderPanel->SetVisibility(ESlateVisibility::Visible);

        if (CustomizeAvatarLoader->spawnedHeadActor == nullptr)
        {
            CustomizeAvatarLoader->LoadHeadModel([this]
            {
                CustomizeAvatarLoader->ResetData();
                CustomizeAvatarLoader->ResetToDefault([this]
                {
             
                });
            });
        }
    },
    [this](FApiException error)
    {
        UE_LOG(LogTemp, Display, TEXT("error"));
    });

  
}

void UAvatarLoaderUI::OnClickTopButton()
{
    int gender = 3;
    if (CustomizeAvatarLoader->GetGender() == EGender::MALE)
    {
        gender = 1;
    }
    if (CustomizeAvatarLoader->GetGender() == EGender::FEMALE)
    {
        gender = 2;
    }
    
    UEconomyHandler::GetEconomyItems("Top", 1, gender, 0, 500, [this](FGetEconomyItemsResult result)
    {
        FEconomyItems economyItem = GetEconomyItem(result.Data[0]);
        CustomizeAvatarLoader->LoadNetworkModel(economyItem);
    },
    [this](FApiException error) 
    {

    });
}

void UAvatarLoaderUI::OnClickBottomButton()
{
    int gender = 3;
    if (CustomizeAvatarLoader->GetGender() == EGender::MALE)
    {
        gender = 1;
    }
    if (CustomizeAvatarLoader->GetGender() == EGender::FEMALE)
    {
        gender = 2;
    }

    UEconomyHandler::GetEconomyItems("Bottom", 1, gender, 0, 500, [this](FGetEconomyItemsResult result)
    {
        FEconomyItems economyItem = GetEconomyItem(result.Data[0]);
        CustomizeAvatarLoader->LoadNetworkModel(economyItem);
    },
    [this](FApiException error)
    {

    });
}

void UAvatarLoaderUI::OnClickMoreButton()
{
    MoreDetailsPanel->SetVisibility(ESlateVisibility::Visible);
}

void UAvatarLoaderUI::OnClickOkButton()
{
    MoreDetailsPanel->SetVisibility(ESlateVisibility::Hidden);
}



FEconomyItems UAvatarLoaderUI::GetEconomyItem(FGetEconomyItemsResultDataInner data)
{
    FEconomyItems economyitem;
    economyitem.templateId = data.TemplateID;
    economyitem.itemCategory = data.ItemCategory;
    economyitem.itemSubCategory = data.ItemSubCategory;
    economyitem.displayName = data.DisplayName;
    economyitem.description = data.Description;
    economyitem.customMetaData = data.CustomMetaData;
    economyitem.style = data.Style;
    economyitem.artifacts = data.Artifacts;
    economyitem.itemSkin = data.ItemSkin;
    economyitem.iD = data.ID;
    economyitem.coreBucket = data.CoreBucket;
    economyitem.occupiedBuckets = data.OccupiedBuckets;
    economyitem.blendshapes = data.Blendshapes;
    economyitem.meshData = data.MeshData;
    economyitem.bonesPhysics = data.BonesPhysics;
    economyitem.boneAdjustments = data.BoneAdjustments;
    economyitem.itemGender = data.ItemGender;
    economyitem.isStackable = data.IsStackable;
    economyitem.isLimitedEdition = data.IsLimitedEdition;
    economyitem.limitedEditionIntialCount = data.LimitedEditionIntialCount;
    economyitem.status = data.Status;
    economyitem.realCurrency = data.RealCurrency;

    FBlendShapesV blendshapes;
    FString blendstrstr = "{";
    blendstrstr.Append("\"blendShapes\":");
    blendstrstr.Append(data.BlendshapeKeys);
    blendstrstr.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(blendstrstr, &blendshapes, 0, 0);
    economyitem.blendshapeKeys = blendshapes;

    if (!data.VirtualCurrency.IsEmpty())
    {
        FVirtualCurrencys virtualcurrencys;
        FString virtualstr = "{";
        virtualstr.Append("\"virtualCurrencys\":");
        virtualstr.Append(data.VirtualCurrency);
        virtualstr.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(virtualstr, &virtualcurrencys, 0, 0);
        economyitem.virtualCurrency = virtualcurrencys;
    }
    if (!data.Tags.IsEmpty())
    {
        FTags tags;
        FString tagstr = "{";
        tagstr.Append("\"tags\":");
        tagstr.Append(data.Tags);
        tagstr.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(tagstr, &tags, 0, 0);
        economyitem.tags = tags;
    }
    if (!data.ItemThumbnailsUrl.IsEmpty())
    {
        FItemThumUrls itemthumburls;
        FString itemthumstr = "{";
        itemthumstr.Append("\"itemThumbnails\":");
        itemthumstr.Append(data.ItemThumbnailsUrl);
        itemthumstr.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(itemthumstr, &itemthumburls, 0, 0);
        economyitem.itemThumbnailsUrl = itemthumburls;
    }

    FEntitlement entitlements;
    FJsonObjectConverter::JsonObjectStringToUStruct(data.Entitlement, &entitlements, 0, 0);
    economyitem.entitlement = entitlements;

    if (!data.ConflictingBuckets.IsEmpty())
    {
        FConflictingBuckets bucketsdata;
        FString bucketdatastring = "{";
        bucketdatastring.Append("\"buckets\":");
        bucketdatastring.Append(data.ConflictingBuckets);
        bucketdatastring.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(bucketdatastring, &bucketsdata, 0, 0);
        economyitem.conflictingBuckets = bucketsdata;
    }
    FConfigs configs;
    FJsonObjectConverter::JsonObjectStringToUStruct(data.Config, &configs, 0, 0);
    economyitem.config = configs;
    return economyitem;
}