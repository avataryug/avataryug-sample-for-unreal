// Fill out your copyright notice in the Description page of Project Settings.

#include "EconomyItemHolder.h"
#include "Kismet/GameplayStatics.h"
#include "JsonObjectConverter.h"
// Sets default values
AEconomyItemHolder::AEconomyItemHolder()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AEconomyItemHolder::BeginPlay()
{
    Super::BeginPlay();
    // if (EconomyItemHolder == nullptr)
    // {
    //     AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
    //     EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
    //     if (EconomyItemHolder == nullptr)
    //     {
    //         EconomyItemHolder = GetWorld()->SpawnActor<AEconomyItemHolder>();
    //     }
    // }
    if (CurrentAvatarChangesHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        CurrentAvatarChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        // CurrentAvatarChangesHolder->SetActorLabel(FString("CurrentAvatarChangesHolder"));
        if (CurrentAvatarChangesHolder == nullptr)
        {
            CurrentAvatarChangesHolder = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
        }
    }
}

// Called every frame
void AEconomyItemHolder::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AEconomyItemHolder::LogOut()
{
    EconomyItems.Empty();
}

bool AEconomyItemHolder::IsCategoryEconomyItemAdded(FString category)
{
    bool isPresent = false;
    for (const FEconomyItems &item : EconomyItems)
    {
        if (item.itemCategory == category && !item.displayName.IsEmpty())
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}

bool AEconomyItemHolder::IsEconomyItemPresent(FString id)
{
    bool isPresent = false;
    for (const FEconomyItems &item : EconomyItems)
    {
        if (item.iD == id)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}
FEconomyItems AEconomyItemHolder::GetEconomyItemWithId(FString id)
{
    FEconomyItems economyitem;
    for (FEconomyItems item : EconomyItems)
    {
        if (item.iD == id)
        {
            economyitem = item;
            break;
        }
    }
    return economyitem;
}

FEconomyItems AEconomyItemHolder::GetEconomyCurrentItemWithId(FString id)
{
    FEconomyItems currentitem;
    for (FEconomyItems item : m_CurrentSelectedItems)
    {
        if (item.iD == id)
        {
            currentitem = item;
            break;
        }
    }
    return currentitem;
}

FCurrentEconomyItemTexture AEconomyItemHolder::GetCurrentEconomyTex(FString id)
{
    FCurrentEconomyItemTexture isPresent;
    for (const FCurrentEconomyItemTexture &item : currentEconomyData)
    {
        if (item.ID == id)
        {
            isPresent = item;
            break;
        }
    }
    return isPresent;
}

TArray<FEconomyItems> AEconomyItemHolder::GetEconomysItemWithCat(FString category)
{
    TArray<FEconomyItems> FoundStructs;
    for (const FEconomyItems &item : EconomyItems)
    {
        if (item.itemCategory == category)
        {
            FoundStructs.Add(item);
        }
    }
    return FoundStructs;
}

void AEconomyItemHolder::AddEconomyItemDataFromAvatar( FGetUserAvatarAllDataResponse result) 
{
    for (int i = 0; i < result.Data.Num(); i++)
    {
            FEconomyItems economyitem;
            economyitem.templateId = result.Data[i].TemplateID;
            economyitem.itemCategory = result.Data[i].ItemCategory;
            economyitem.artifacts = result.Data[i].Artifacts;
            economyitem.itemSkin = result.Data[i].ItemSkin;
            economyitem.iD = result.Data[i].ID;
            economyitem.coreBucket = result.Data[i].CoreBucket;
      
            FConfigs configs;
            FJsonObjectConverter::JsonObjectStringToUStruct(result.Data[i].Config, &configs,0,0);
            economyitem.config = configs;

            FConflictingBuckets bucketsdata;
            FString bucketdatastring = "{";
            bucketdatastring.Append("\"buckets\":");
            bucketdatastring.Append(result.Data[i].ConflictingBuckets);
            bucketdatastring.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(bucketdatastring, &bucketsdata,0,0);
            economyitem.conflictingBuckets = bucketsdata;

            FBlendShapesV blendshapes;
            FString blendstrstr = "{";
            blendstrstr.Append("\"blendShapes\":");
            blendstrstr.Append(result.Data[i].BlendshapeKeys);
            blendstrstr.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(blendstrstr, &blendshapes,0,0);
            economyitem.blendshapeKeys = blendshapes;
        
            EconomyItems.Add(economyitem);

            FString ids = economyitem.iD;
            if (CurrentAvatarChangesHolder != nullptr)
            {
                if (CurrentAvatarChangesHolder->IsItemPresent(ids))
                {
                    if (!IsCurrentSelectedEconomyItemPresent(ids))
                    {
                        m_CurrentSelectedItems.Add(economyitem);
                    }
                }
            }
    }
}
FEconomyItems AEconomyItemHolder::GetEconomyItem(FGetEconomyItemsResultDataInner data)
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
            FJsonObjectConverter::JsonObjectStringToUStruct(blendstrstr, &blendshapes,0,0);
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
            FJsonObjectConverter::JsonObjectStringToUStruct(data.Entitlement, &entitlements,0,0);
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
            FJsonObjectConverter::JsonObjectStringToUStruct(data.Config, &configs,0,0);
            economyitem.config = configs;
            return economyitem;
}
void AEconomyItemHolder::AddEconomyItemData(FGetEconomyItemsResult result)
{
    TArray<FEconomyItems> FilteredItems;
    FString category = "";
    if (result.Data.Num() > 0)
    {
        category = result.Data[0].ItemCategory;
        for (int i = 0; i < EconomyItems.Num(); i++)
        {
            if(EconomyItems[i].itemCategory != category)
            {
                FilteredItems.Add( EconomyItems[i]);
            }
        }
        EconomyItems.Empty();
        for (int i = 0; i < FilteredItems.Num(); i++)
        {
            EconomyItems.Add( FilteredItems[i]);
        }
    }
    for (int i = 0; i < result.Data.Num(); i++)
    {
        if (!IsEconomyItemPresent(result.Data[i].ID))
        {
            FEconomyItems economyitem = GetEconomyItem(result.Data[i]);
            int32 PlatformValue = 0;
#if PLATFORM_ANDROID
            PlatformValue = 0; // Set to 0 for Android
#endif
#if PLATFORM_IOS
            PlatformValue = 1; // Set to 2 for iOS
#endif
            bool isThumbnailPResnet = false;
            for (int j = 0; j < economyitem.itemThumbnailsUrl.itemThumbnails.Num(); j++)
            {
                if (economyitem.itemThumbnailsUrl.itemThumbnails[j].device == PlatformValue)
                {
                    isThumbnailPResnet = true;
                    break;
                }
            }
            if (isThumbnailPResnet)
            {
                EconomyItems.Add(economyitem);
            }
            FString ids = economyitem.iD;
            if (CurrentAvatarChangesHolder != nullptr)
            {
                if (CurrentAvatarChangesHolder->IsItemPresent(ids))
                {
                    if (!IsCurrentSelectedEconomyItemPresent(ids))
                    {
                        m_CurrentSelectedItems.Add(economyitem);
                    }
                }
            }
        }
    }
}

bool AEconomyItemHolder::IsCurrentSelectedEconomyItemPresent(FString id)
{
    bool isCurrentItemPresent = false;
    for (const FEconomyItems &items : m_CurrentSelectedItems)
    {
        if (items.iD == id)
        {
            isCurrentItemPresent = true;
            break;
        }
    }
    return isCurrentItemPresent;
}

void AEconomyItemHolder::OnQueueRemoveItem()
{
    if (EconomyItems.Num() > 0)
    {
        if (EconomyItems.Num() > itemListLimit)
        {
            FString firstcat;
            firstcat = EconomyItems[0].itemCategory;

            EconomyItems.RemoveAll([firstcat](const FEconomyItems &Item)
                                   { return Item.itemCategory == firstcat; });

            OnQueueRemoveItem();
        }
    }
}