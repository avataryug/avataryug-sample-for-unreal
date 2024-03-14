// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarLoaderBase.h"
#include "JsonObjectConverter.h"
#include "Kismet/GameplayStatics.h"
#include "ImageUtils.h"
#include "Kismet/KismetStringLibrary.h"
#include "../AvatarLoader/AvatarHandler.h"
#include "TimerManager.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "Components/SkeletalMeshComponent.h"
#include "AvataryugFunctionLibrary.h"
#include "Serialization/JsonSerializerMacros.h"
#include "../DataHolders/AvataryugData.h"
#include "Engine/TextureRenderTarget2D.h"
// Sets default values
AAvatarLoaderBase::AAvatarLoaderBase()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
    PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AAvatarLoaderBase::BeginPlay()
{
    Super::BeginPlay();

    Gender = EGender::MALE;

    if (BodyDynamicMaterial == nullptr)
    {
        BodyDynamicMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
    }
    if (HeadDynamicMaterial == nullptr)
    {
        HeadDynamicMaterial = UMaterialInstanceDynamic::Create(HeadMaterial, this);
    }
    if (HairDynamicMaterial == nullptr)
    {
        HairDynamicMaterial = UMaterialInstanceDynamic::Create(HairMaterial, this);
    }
    if (EyeballDynamicMaterial == nullptr)
    {
        EyeballDynamicMaterial = UMaterialInstanceDynamic::Create(EyeballMaterial, this);
    }
    if (MouthDynamicMaterial == nullptr)
    {
        MouthDynamicMaterial = UMaterialInstanceDynamic::Create(MouthMaterial, this);
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

    if (DataHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ADataHolder::StaticClass());
        DataHolder = Cast<ADataHolder>(FoundActor);
        if (DataHolder == nullptr)
        {
            DataHolder = GetWorld()->SpawnActor<ADataHolder>();
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

    if (EconomyItemHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
        EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
        if (EconomyItemHolder == nullptr)
        {
            EconomyItemHolder = GetWorld()->SpawnActor<AEconomyItemHolder>();
        }
    }

    if (CameraControllerPaw == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACameraControllerPawn::StaticClass());
        CameraControllerPaw = Cast<ACameraControllerPawn>(FoundActor);
        if (CameraControllerPaw == nullptr)
        {
            CameraControllerPaw = GetWorld()->SpawnActor<ACameraControllerPawn>();
        }
    }

    // SetParentPoint();
    FOnReceiveModelData.BindUFunction(this, "OnReceiveModelByte");
    FOnReceiveFaceModelData.BindUFunction(this, "OnReceiveFaceModelData");
    ReceiveHairTexture.BindUFunction(this, "OnReceiveHairTexture");
    FOnReceiveClipData.BindUFunction(this, "OnReceiveClipByte");
}
EGender AAvatarLoaderBase::GetGender()
{
    // EGender TempGender;
    // TempGender = EGender::MALE;
    if (UserDetailHolder)
    {
        Gender = UserDetailHolder->UserDetails.Gender;
    }
    return EGender();
}
// Called every frame
void AAvatarLoaderBase::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAvatarLoaderBase::SetParentPoint()
{
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;

    if (SpawnedCustomizeDefaultParentClone == nullptr)
    {
        if (BP_EmptyActor != nullptr)
        {
            SpawnedCustomizeDefaultParentClone = GetWorld()->SpawnActor<AEmptyActor>(BP_EmptyActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            SpawnedCustomizeDefaultParentClone->AttachToActor(this, AttachmentTransformRules);
            // SpawnedCustomizeDefaultParentClone->SetActorLabel(FString("CustomizeDefaultParent(Clone)"));
        }
    }
}

void AAvatarLoaderBase::SetParentVisibility(bool onbaording, bool homeparent, bool customizeparent)
{
    if (SpawnedOnboardingParent)
    {
        if (onbaording)
        {
            SpawnedOnboardingParent->SetActorLocation(FVector(0, 0, 0));
        }
        else
        {
            SpawnedOnboardingParent->SetActorLocation(FVector(0, 0, 1000));
        }
    }
    if (SpawnedHomeParent)
    {
        if (homeparent)
        {
            SpawnedHomeParent->SetActorLocation(FVector(0, 0, 0));
        }
        else
        {
            SpawnedHomeParent->SetActorLocation(FVector(0, 0, 1000));
        }
    }
    if (SpawnedCustomizeParent)
    {
        if (customizeparent)
        {
            SpawnedCustomizeParent->SetActorLocation(FVector(0, 0, 0));
        }
        else
        {
            SpawnedCustomizeParent->SetActorLocation(FVector(0, 0, 1000));
        }
    }
}

void AAvatarLoaderBase::LoadStartData()
{
    if (BodyDynamicMaterial == nullptr)
    {
        BodyDynamicMaterial = UMaterialInstanceDynamic::Create(BodyMaterial, this);
    }
    if (HeadDynamicMaterial == nullptr)
    {
        HeadDynamicMaterial = UMaterialInstanceDynamic::Create(HeadMaterial, this);
    }
    if (HairDynamicMaterial == nullptr)
    {
        HairDynamicMaterial = UMaterialInstanceDynamic::Create(HairMaterial, this);
    }
    if (EyeballDynamicMaterial == nullptr)
    {
        EyeballDynamicMaterial = UMaterialInstanceDynamic::Create(EyeballMaterial, this);
    }
    if (MouthDynamicMaterial == nullptr)
    {
        MouthDynamicMaterial = UMaterialInstanceDynamic::Create(MouthMaterial, this);
    }
    UAvataryugData *AvataryugDataInstance = NewObject<UAvataryugData>(); // Create an instance
    TArray<FString> bodyTattoos = AvataryugDataInstance->bodytattos;     // Access the member

    for (int i = 0; i < bodyTattoos.Num(); i++)
    {
        // FString Category = Head2DCategories.IsValidIndex(i) ? Head2DCategories[i] : FString(); // Get the category from the array or an empty string if index is invalid

        // Construct the parameter name as a FName
        // FName ParameterName = FName(*Category);
        BodyDynamicMaterial->SetTextureParameterValue(FName(bodyTattoos[i]), EmptyTexture);
    }
}

void AAvatarLoaderBase::LoadHeadModel()
{
    UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--LoadHeadModel"));
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;

    if (spawnedHeadActor == nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--spawnedHeadActor == nullptr"));
        if (BP_HeadActor != nullptr)
        {

            const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
            // FAttachmentTransformRules AttachmentRules(
            // EAttachmentRule::SnapToTarget, // Location rule
            // EAttachmentRule::SnapToTarget, // Rotation rule
            // EAttachmentRule::KeepRelative, // Scale rule
            // false // Weld simulated bodies
            // );

            spawnedHeadActor = GetWorld()->SpawnActor<AHeadActor>(BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            // AAvatarHandler* AvatarHandlerInstance = AAvatarHandler::GetInstance();

            // spawnedCloneHeadActor = GetWorld()->SpawnActor<AHeadActor>(BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            if (APIEvents->isCustomize)
            {
                UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--AHeadActor.isCustomize"));
                spawnedHeadActor->AttachToActor(this, AttachmentTransformRules);
                // spawnedCloneHeadActor->AttachToActor(SpawnedCustomizeDefaultParentClone, AttachmentTransformRules);
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--AHeadActor.isNOTCustomize"));
                spawnedHeadActor->AttachToActor(this, AttachmentTransformRules);
            }
            // spawnedCloneHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            // spawnedCloneHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            spawnedHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
            spawnedHeadActor->SetMouthMaterial(MouthDynamicMaterial);
            LoadDetaultModels();
            // AvatarHandlerInstance->LoadInventoryPropDetail();
        }
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--else"));
        if (BP_HeadActor != nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->BP_HeadActor"));
            // LoadDetaultModels();
        }
    }
}
void AAvatarLoaderBase::LoadHeadModel(TFunction<void()> OnComplete)
{
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (spawnedHeadActor == nullptr)
    {
        if (BP_HeadActor != nullptr)
        {
            const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
            spawnedHeadActor = GetWorld()->SpawnActor<AHeadActor>(BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            spawnedHeadActor->AttachToActor(this, AttachmentTransformRules);
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            spawnedHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
                        spawnedHeadActor->SetMouthMaterial(MouthDynamicMaterial);
            OnComplete();
        }
    } else {
       OnComplete();
    }
}
void AAvatarLoaderBase::LoadCustomizeModel()
{
    UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--LoadCustomizeModel"));
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (spawnedHeadActor == nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--spawnedHeadActor == nullptr"));
        if (BP_HeadActor != nullptr)
        {
            UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AAvatarLoaderBase--AHeadActor != nullptr"));
            const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
            spawnedHeadActor = GetWorld()->SpawnActor<AHeadActor>(BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            AAvatarHandler *AvatarHandlerInstance = AAvatarHandler::GetInstance();

            UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AvatarHandlerInstance--  "));

            // spawnedCloneHeadActor = GetWorld()->SpawnActor<AHeadActor>(BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            // if(APIEvents->isCustomize)
            // {
            //     spawnedCustomizeHeadActor->AttachToActor(this, AttachmentTransformRules);
            //     // spawnedCloneHeadActor->AttachToActor(SpawnedCustomizeDefaultParentClone, AttachmentTransformRules);
            // }
            // else
            // {
            // AAvatarHandler* AvatarHandlerInstance = AAvatarHandler::GetInstance();
            spawnedHeadActor->AttachToActor(this, AttachmentTransformRules);
            // }
            // spawnedCloneHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            // spawnedCloneHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            spawnedHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
            spawnedHeadActor->SetMouthMaterial(MouthDynamicMaterial);
            LoadDetaultModels();
        }
    }
}



void AAvatarLoaderBase::ResetAvatarLoader()
{
    HeadCoreBuck = "";
    BodyDynamicMaterial = nullptr;
    HeadDynamicMaterial = nullptr;
    EyeballDynamicMaterial = nullptr;

    loadDefaultModellist.Empty();
    defaultModelList.Empty();
    bodyPoints.Empty();
    lastLoadedTattoos.Empty();

    currentTopData = FEconomyItems();
    currentWristwearData = FEconomyItems();
    currentBottomData = FEconomyItems();
    currentOutfitData = FEconomyItems();
    currentFootwearData = FEconomyItems();
    currentHandwearData = FEconomyItems();
    currentLispData = FEconomyItems();
    currentfacialHairData = FEconomyItems();
    currentEyeballData = FEconomyItems();
    currentEyebrowData = FEconomyItems();
    currentHairData = FEconomyItems();
    currentHeadwearData = FEconomyItems();
    currentFaceshapeData = FEconomyItems();
    currentEarshapeData = FEconomyItems();
    currentNoseshapeData = FEconomyItems();
    currentEyebrowshapeData = FEconomyItems();
    currentEyeshapeData = FEconomyItems();
    currentLipshapeData = FEconomyItems();
    currentskintoneData = FEconomyItems();

    networkModelQueue.Empty();

    HairModel = nullptr;
    HeadwearModel = nullptr;
}
void AAvatarLoaderBase::CheckMissingModelAfterRemovingSameModel(FEconomyItems modelData)
{
    bool loadTop = false;
    bool loadBottom = false;
    bool loadFootwear = false;
    bool loadHandwear = false;

    if (modelData.itemCategory == "Top")
    {
        bool istopPresent = false;
        bool isbottomPresent = false;
        bool isFootwearPresent = false;

        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (!istopPresent && bodyPoints[i]->BucketName == "upperbody_sleeve_short" || bodyPoints[i]->BucketName == "upperbody_sleeve_full" || bodyPoints[i]->BucketName == "upperbody_sleeveless")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    istopPresent = true;
                }
            }

            if (!isbottomPresent && bodyPoints[i]->BucketName == "lowerbody_without_foot" || bodyPoints[i]->BucketName == "lowerbody_till_knee")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isbottomPresent = true;
                }
            }

            if (!isFootwearPresent && bodyPoints[i]->BucketName == "lowerbody_foot_both")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                }
            }
        }
        if (!istopPresent)
        {
            loadTop = true;
        }
        if (!isbottomPresent)
        {
            loadBottom = true;
        }
        if (!isFootwearPresent)
        {
            loadFootwear = true;
        }
    }

    if (modelData.itemCategory == "Bottom")
    {
        bool isBottomPresent = false;
        bool isTOpPresent = false;
        bool isFootwearPresent = false;

        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (!isBottomPresent && (bodyPoints[i]->BucketName == "lowerbody_without_foot" ||
                                     bodyPoints[i]->BucketName == "lowerbody_till_knee"))
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isBottomPresent = true;
                }
            }

            if (!isTOpPresent && (bodyPoints[i]->BucketName == "upperbody_sleeve_short" ||
                                  bodyPoints[i]->BucketName == "upperbody_sleeve_full" ||
                                  bodyPoints[i]->BucketName == "upperbody_sleeveless"))
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isTOpPresent = true;
                }
            }
            if (!isFootwearPresent && (bodyPoints[i]->BucketName == "lowerbody_foot_both"))
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                }
            }
        }
        // if (!isBottomPresent)
        // {
        loadBottom = !isBottomPresent;
        // }
        // if (!isTOpPresent)
        // {
        loadTop = !isTOpPresent;
        // }
        // if (!isFootwearPresent)
        // {
        loadFootwear = !isFootwearPresent;
        // }
    }

    if (modelData.itemCategory == "Outfit")
    {
        UE_LOG(LogTemp, Display, TEXT("CAtegory is  Outfit---->>%s"), *modelData.displayName);
        bool isFootwearPresent = false;
        bool isTOpPresent = false;
        bool isBottomPresent = false;
        bool isHandPResent = false;

        for (AGltfStaticActorPoint *Item : bodyPoints)
        {

            if (!isBottomPresent && (Item->BucketName == "lowerbody_without_foot" || Item->BucketName == "lowerbody_till_knee"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isBottomPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isbottomPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
            if (!isTOpPresent && (Item->BucketName == "upperbody_sleeve_short" || Item->BucketName == "upperbody_sleeve_full" || Item->BucketName == "upperbody_sleeveless"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isTOpPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isTopPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
            if (!isFootwearPresent && (Item->BucketName == "lowerbody_foot_both"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                }
            }
            if (!isHandPResent && (Item->BucketName == "upperbody_hand_both"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isHandPResent = true;
                }
            }
        }

        loadTop = !isTOpPresent;
        loadBottom = !isBottomPresent;
        loadFootwear = !isFootwearPresent;
        loadHandwear = !isHandPResent;
        addDelay = loadBottom;
    }
    if (modelData.itemCategory == "Footwear")
    {
        bool isFootwearPresent = false;
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (!isFootwearPresent && (bodyPoints[i]->BucketName == "lowerbody_foot_both"))
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                }
            }
        }
        // if (!isFootwearPresent)
        // {
        loadFootwear = !isFootwearPresent;
        // }
    }
    if (modelData.itemCategory == "Handwear")
    {
        bool isHandPResent = false;
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (!isHandPResent && (bodyPoints[i]->BucketName == "upperbody_hand_both"))
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isHandPResent = true;
                }
            }
        }
        // if (!isHandPResent)
        // {
        loadHandwear = !isHandPResent;
        // }
    }

    FString gender;
    switch (UserDetailHolder->UserDetails.Gender)
    {
    case EGender::MALE:
        gender = "2";
        break;

    case EGender::FEMALE:
        gender = "1";
        break;
    }

    TArray<FModelDataResponce> defaultModel = ULocalDataFunctionLibrary::GetDefaultModelList(gender);
    if (loadTop)
    {
        UE_LOG(LogTemp, Display, TEXT("======> Adding missing TOP Model-->>"));
        loadDefaultModellist.Add(defaultModel[0]);
        OnLoadQueueDefaultModel([this]
                                { UE_LOG(LogTemp, Display, TEXT("ADDING DEFAULT TOP---->")); });
        // OnLoadQueueDefaultModels();
    }
    if (loadBottom)
    {
        APIEvents->ShowLoading();
        UE_LOG(LogTemp, Display, TEXT("======> Adding missing BOTTOM Model-->>"));
        loadDefaultModellist.Add(defaultModel[1]);
        if (addDelay)
        {
            FTimerHandle TimerHandle_Del;
            GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::TestAddingDelay, 5.0f, false);
        }
        else
        {
            OnLoadQueueDefaultModel([this]
                                    { UE_LOG(LogTemp, Display, TEXT("ADDING DEFAULT Bottom---->")); });
        }
    }
    if (loadFootwear)
    {
        loadDefaultModellist.Add(defaultModel[2]);
        OnLoadQueueDefaultModel([this] {});
        //  OnLoadQueueDefaultModels();
    }
    if (loadHandwear)
    {
        loadDefaultModellist.Add(defaultModel[3]);
        OnLoadQueueDefaultModel([this] {});
        //  OnLoadQueueDefaultModels();
    }
}

void AAvatarLoaderBase::TestAddingDelay()
{
    OnLoadQueueDefaultModel([this]
                            { UE_LOG(LogTemp, Display, TEXT("======> Loading missing BOTTOM Model- wiht Delay->>")); });
}
void AAvatarLoaderBase::AddLoadingDelay()
{
    APIEvents->HideLoading();
}

void AAvatarLoaderBase::ClearCurrent()
{
    currentHandwearData = currentFootwearData = currentTopData = currentWristwearData = FEconomyItems();
    currentBottomData = currentLispData = currentfacialHairData = currentEyeballData = currentEyebrowData = FEconomyItems();
    currentOutfitData = currentHairData = currentHeadwearData = currentFaceshapeData = currentEarshapeData = FEconomyItems();
    currentNoseshapeData = currentEyebrowshapeData = currentEyeshapeData = currentLipshapeData = currentskintoneData = FEconomyItems();
}

void AAvatarLoaderBase::CheckMissingAfterModelLoad(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    bool loadTop = false;
    bool loadBottom = false;
    bool loadFootwear = false;
    bool loadHandwear = false;

    if (modelData.itemCategory == "Top")
    {
        bool isbottomPresent = false;
        bool isFootwearPresent = false;

        for (AGltfStaticActorPoint *Item : bodyPoints)
        {
            if (!isbottomPresent && (Item->BucketName == "lowerbody_without_foot" || Item->BucketName == "lowerbody_till_knee"))
            {
                // isbottomPresent = Item->Children.Num() > 0;
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isbottomPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isbottomPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
            if (!isFootwearPresent && Item->BucketName == "lowerbody_foot_both")
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isFootwearPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
        }

        loadBottom = !isbottomPresent;
        loadFootwear = !isFootwearPresent;

        FString BoolAsString = loadBottom ? TEXT("true") : TEXT("false");
        UE_LOG(LogTemp, Display, TEXT("ADDED---loadBottom ---->>%s"), *BoolAsString);

        FString BoolAsloadFootwear = loadFootwear ? TEXT("true") : TEXT("false");
        UE_LOG(LogTemp, Display, TEXT("ADDED---loadFootwear ---->>%s"), *BoolAsloadFootwear);
    }
    if (modelData.itemCategory == "Bottom")
    {
        bool isTopPresent = false;
        bool isFootwearPresent = false;

        for (AGltfStaticActorPoint *Item : bodyPoints)
        {
            if (!isTopPresent && (Item->BucketName == "upperbody_sleeve_short" || Item->BucketName == "upperbody_sleeve_full" || Item->BucketName == "upperbody_sleeveless"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isTopPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isTopPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
            if (!isFootwearPresent && Item->BucketName == "lowerbody_foot_both")
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isFootwearPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
        }

        loadTop = !isTopPresent;
        loadFootwear = !isFootwearPresent;

        FString BoolAsString = loadTop ? TEXT("true") : TEXT("false");
        UE_LOG(LogTemp, Display, TEXT("ADDED---loadTop ---->>%s"), *BoolAsString);

        FString BoolAsloadFootwear = loadFootwear ? TEXT("true") : TEXT("false");
        UE_LOG(LogTemp, Display, TEXT("ADDED---loadFootwear ---->>%s"), *BoolAsloadFootwear);
    }

    if (modelData.itemCategory == "Outfit")
    {
        bool isFootwearPresent = false;
        bool isHandPresent = false;
        bool isTopPresent = false;
        bool isBottomPresent = false;
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (!isFootwearPresent && bodyPoints[i]->BucketName == "lowerbody_foot_both")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isFootwearPresent = true;
                }
            }
            if (!isHandPresent && bodyPoints[i]->BucketName == "upperbody_hand_both")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isHandPresent = true;
                }
            }
            if (!isTopPresent && bodyPoints[i]->BucketName == "upperbody_sleeve_short" || bodyPoints[i]->BucketName == "upperbody_sleeve_full" || bodyPoints[i]->BucketName == "upperbody_sleeveless")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    UE_LOG(LogTemp, Display, TEXT("Removing TOP---->>"));
                    isTopPresent = true;
                }
            }
            if (!isBottomPresent && bodyPoints[i]->BucketName == "lowerbody_without_foot" || bodyPoints[i]->BucketName == "lowerbody_till_knee")
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    UE_LOG(LogTemp, Display, TEXT("Removing isBottomPresent---->>"));
                    isBottomPresent = true;
                }
            }
        }
        if (isTopPresent || isBottomPresent)
        {
            UE_LOG(LogTemp, Display, TEXT("Conflicts not available---->>"));
            APIEvents->ShowErrorNotification("404", "Conflicts Not Available");
        }

        loadFootwear = !isFootwearPresent;
        loadHandwear = !isHandPresent;
    }

    if (modelData.itemCategory == "Footwear")
    {
        bool isTopPresent = false;
        bool isBottomPresent = false;
        bool isOutfitpresnet = false;

        for (AGltfStaticActorPoint *Item : bodyPoints)
        {
            if (!isTopPresent && (Item->BucketName == "upperbody_sleeve_short" || Item->BucketName == "upperbody_sleeve_full" || Item->BucketName == "upperbody_sleeveless"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isTopPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isTopPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }

            if (!isBottomPresent && (Item->BucketName == "lowerbody_without_foot" || Item->BucketName == "lowerbody_till_knee"))
            {
                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isBottomPresent = true;
                    UE_LOG(LogTemp, Display, TEXT("ADDED---isbottomPresent COUNT---->>%d"), AttachedActors.Num());
                }
            }
            if (!isOutfitpresnet && (Item->BucketName == "fullbody_without_head" || Item->BucketName == "fullbody_with_head_foot" || Item->BucketName == "fullbody_without_head_foot"))
            {

                TArray<AActor *> AttachedActors;
                Item->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    isOutfitpresnet = true;
                }
            }
        }

        if (!isOutfitpresnet)
        {
            loadTop = !isTopPresent;
            loadBottom = !isBottomPresent;
        }
    }
    FString gender;
    switch (UserDetailHolder->UserDetails.Gender)
    {
    case EGender::MALE:
        gender = "2";
        break;

    case EGender::FEMALE:
        gender = "1";
        break;
    }

    TArray<FModelDataResponce> defaultModel = ULocalDataFunctionLibrary::GetDefaultModelList(gender);
    if (loadTop)
    {
        loadDefaultModellist.Add(defaultModel[0]);
        OnLoadQueueDefaultModel([this] {});
    }
    if (loadBottom)
    {
        loadDefaultModellist.Add(defaultModel[1]);
        OnLoadQueueDefaultModel([this] {});
    }
    if (loadFootwear)
    {
        loadDefaultModellist.Add(defaultModel[2]);
        OnLoadQueueDefaultModel([this] {});
    }
    if (loadHandwear)
    {
        loadDefaultModellist.Add(defaultModel[3]);
        OnLoadQueueDefaultModel([this] {});
    }

    FTimerHandle TimerHandle_Del;
    GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 1.0f, false);
}

void AAvatarLoaderBase::LoadDetaultModels()
{
    UE_LOG(LogTemp, Display, TEXT("======> LoadDetaultModels-->>"));
    // if(APIEvents->isCustomize)
    // {
    //     if(APIEvents->isMale)
    //     {
    //         TArray<FModelDataResponce> defaultModel = ULocalDataFunctionLibrary::GetDefaultModelList("2");

    //         for (int i = 0; i < defaultModel.Num(); i++)
    //         {
    //         loadDefaultModellist.Add(defaultModel[i]);
    //         cloneDefaultModelList.Add(defaultModel[i]);
    //         }
    //         UE_LOG(LogTemp, Display,TEXT("======> LoadDetaultModels--Male"));
    //         OnLoadQueueDefaultModels();
    //     }
    //     else
    //     {
    //         TArray<FModelDataResponce> defaultModel = ULocalDataFunctionLibrary::GetDefaultModelList("1");

    //         for (int i = 0; i < defaultModel.Num(); i++)
    //         {
    //             loadDefaultModellist.Add(defaultModel[i]);
    //             cloneDefaultModelList.Add(defaultModel[i]);
    //         }
    //         UE_LOG(LogTemp, Display,TEXT("======> LoadDetaultModelFemale"));
    //         OnLoadQueueDefaultModels();
    //     }
    // }
    // else
    // {
    if (UserDetailHolder != nullptr)
    {
        if (UserDetailHolder->UserDetails.Gender == EGender::MALE)
        {

            TArray<FModelDataResponce> defaultModel = ULocalDataFunctionLibrary::GetDefaultModelList("1");

            for (int i = 0; i < defaultModel.Num(); i++)
            {
                loadDefaultModellist.Add(defaultModel[i]);
                // cloneDefaultModelList.Add(defaultModel[i]);
            }
            UE_LOG(LogTemp, Display, TEXT("======> LoadDetaultModels--Male"));
            // OnLoadQueueDefaultModels();
        }
        else
        {
            TArray<FModelDataResponce> defaultModels = ULocalDataFunctionLibrary::GetDefaultModelList("2");

            for (int i = 0; i < defaultModels.Num(); i++)
            {
                loadDefaultModellist.Add(defaultModels[i]);
                // cloneDefaultModelList.Add(defaultModel[i]);
            }
            UE_LOG(LogTemp, Display, TEXT("======> LoadDetaultModelFemale"));
            // OnLoadQueueDefaultModels();
        }
        //   UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::MALE : EGender::FEMALE;
    }
    // }
}

void AAvatarLoaderBase::FunctionToCallAfterOneSecond(TFunction<void()> OnComplete)
{
    UE_LOG(LogTemp, Display, TEXT("======> FunctionToCallAfterOneSecond--->>"));
    OnComplete();
}
void AAvatarLoaderBase::OnDefaultModelCallback(UglTFRuntimeAsset *asset)
{
    APIEvents->ShowLoading();
    if (asset != nullptr)
    {
        // UE_LOG(LogTemp, Display,TEXT("======> OnDefaultModelCallback %s"),*defaultModelList[0].data.MainCatID);
        FActorSpawnParameters spawnparams;
        spawnparams.Owner = this;
        if (GltfActor_BP != nullptr)
        {

            if (APIEvents->isCustomize)
            {
                UE_LOG(LogTemp, Display, TEXT("======> APIEvents->isCustomize===>>> %s"), *modelDataRes.data.GlbPath);
                const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                AGltfActor *modeler = GetWorld()->SpawnActor<AGltfActor>(GltfActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);

                modeler->Asset = asset;
                LoadedModelList.Add(modeler);
                LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                              { return Object == nullptr; });

                modeler->LoadModel(modelDataRes.data.MainCatID);
                // AddDefaultBodyPart(modeler,modelDataRes);
                modeler->SetBodyMaterial(BodyDynamicMaterial, "body");
                // cloneModel->LoadModel(modelDataRes.data.MainCatID);
                AddNewDefaultBodyPart(modeler, modelDataRes, [this]
                                      {
                     UE_LOG(LogTemp, Display,TEXT("======> APIEvents---------AddNewDefaultBodyPart===>>> %s"),*modelDataRes.data.MainCatID);
                    OnLoadQueueDefaultModel([this]{}); });
                // DuplicateActor(cloneModel,modelDataRes);

                // cloneModel->SetBodyMaterial(BodyDynamicMaterial, "body");
                // defaultModelList.RemoveAt(0);
                // OnLoadQueueDefaultModel([this]{});
            }
            else
            {
                UE_LOG(LogTemp, Display, TEXT("======> APIEvents->isCustomize==NOT=>>> %s"), *modelDataRes.data.GlbPath);
                const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                AGltfActor *modeler = GetWorld()->SpawnActor<AGltfActor>(GltfActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);

                // AGltfActor *cloneModel = GetWorld()->SpawnActor<AGltfActor>(GltfActor_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
                // cloneModel->Asset = asset;

                modeler->Asset = asset;
                LoadedModelList.Add(modeler);
                LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                              { return Object == nullptr; });

                // CloneLoadedModelList.Add(cloneModel);
                // CloneLoadedModelList.RemoveAllSwap([](AGltfActor* Object) { return Object == nullptr; });

                modeler->LoadModel(modelDataRes.data.MainCatID);
                // cloneModel->LoadModel(modelDataRes.data.MainCatID);
                modeler->SetBodyMaterial(BodyDynamicMaterial, "body");
                AddNewDefaultBodyPart(modeler, modelDataRes, [this]
                                      {
                     UE_LOG(LogTemp, Display,TEXT("======> APIEvents---------AddNewDefaultBodyPart===>>> %s"),*modelDataRes.data.MainCatID);
                    OnLoadQueueDefaultModel([this]{}); });
                // DuplicateActor(cloneModel,modelDataRes);

                // cloneModel->SetBodyMaterial(BodyDynamicMaterial, "body");
                // defaultModelList.RemoveAt(0);
                //  OnLoadQueueDefaultModel([this]{});
            }
        }
    }
}

void AAvatarLoaderBase::AddDefaultBodyPart(AGltfActor *gltfActor, FModelDataResponce modelDataResponce)
{
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    int index = 0;
    bool isPresent = false;

    TArray<FString> buckets = UKismetStringLibrary::ParseIntoArray(modelDataResponce.data.CoreBucket, TEXT("/"), true);
    FString bucketname = buckets[0];

    if (buckets.Num() > 1)
    {
        bucketname = buckets[1];
    }
    AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));


    AGltfStaticActorPoint *bodyPoint = nullptr;
    //  AGltfStaticActorPoint *ClonebodyPoint = nullptr;

    if (bodyPoints.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (bodyPoints[i]->BucketName == bucketname)
            {
                bodyPoint = bodyPoints[i];
                isPresent = true;
            }
        }
    }

    if (!isPresent)
    {
        bodyPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(BucketPoint_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        bodyPoint->BucketName = bucketname;

        FString NewbodyPointName = bucketname;
        UE_LOG(LogTemp, Display, TEXT("<---COmpleted MODEL-bucketname--%s>>"), *NewbodyPointName);
        bodyPoint->AttachToActor(this, AttachmentTransformRules);
        bodyPoints.Add(bodyPoint);
        const FAttachmentTransformRules AttachmentTransformRuler = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        gltfActor->AttachToActor(bodyPoint, AttachmentTransformRuler);
        AvatarHandlerInstance->ForCustomizeAvatar->GltfModelList.Add(gltfActor);
        FString NewgvxName = modelDataResponce.data.MainCatID;
        // gltfActor->SetActorLabel(*NewgvxName,true);
        UE_LOG(LogTemp, Display, TEXT("<---COmpleted MODEL--->>"));

        //    }
    }
}

void AAvatarLoaderBase::DuplicateActor(AGltfActor *gltfActor, FModelDataResponce modelDataResponce)
{
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    int index = 0;
    bool isPresent = false;

    TArray<FString> buckets = UKismetStringLibrary::ParseIntoArray(modelDataResponce.data.CoreBucket, TEXT("/"), true);
    FString bucketname = buckets[0];

    if (buckets.Num() > 1)
    {
        bucketname = buckets[1];
    }

    AGltfStaticActorPoint *ClonebodyPoint = nullptr;

    if (cloneBodyPoints.Num() > 0)
    {
        for (int i = 0; i < cloneBodyPoints.Num(); i++)
        {
            if (cloneBodyPoints[i]->BucketName == bucketname)
            {
                ClonebodyPoint = cloneBodyPoints[i];
                isPresent = true;
            }
        }
    }

    if (!isPresent)
    {
        ClonebodyPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(BucketPoint_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        ClonebodyPoint->BucketName = bucketname;

        FString NewbodyPointName = bucketname;
        // bodyPoint->Rename(*NewbodyPointName);
        //  ClonebodyPoint->SetActorLabel(*NewbodyPointName,true);
        //    if(APIEvents->isCustomize)
        //    {
        ClonebodyPoint->AttachToActor(SpawnedCustomizeDefaultParentClone, AttachmentTransformRules);
        cloneBodyPoints.Add(ClonebodyPoint);
        //    }
    }

    for (int i = 0; i < cloneBodyPoints.Num(); i++)
    {
        if (cloneBodyPoints[i]->BucketName == bucketname)
        {
            TArray<AActor *> AttachedActors;
            cloneBodyPoints[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() > 0)
            {
                AttachedActors[0]->Destroy();
            }
        }
    }

    FConflictList ConflictList;
    FJsonObjectConverter::JsonObjectStringToUStruct(modelDataResponce.data.ConflictingBuckets, &ConflictList,0,0);

    for (int k = 0; k < ConflictList.conflits.Num(); k++)
    {
        for (int j = 0; j < cloneBodyPoints.Num(); j++)
        {
            if (cloneBodyPoints[j]->BucketName == ConflictList.conflits[k].name)
            {
                TArray<AActor *> AttachedActors;
                cloneBodyPoints[j]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    AttachedActors[0]->Destroy();
                }
            }
        }
    }

    gltfActor->AttachToActor(ClonebodyPoint, AttachmentTransformRules);
    FString NewgvxName = modelDataResponce.data.MainCatID;
    ;
    UE_LOG(LogTemp, Display, TEXT("<---COmpleted MODEL--All->>"));
    FTimerHandle TimerHandle_Del;
    GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
}


void AAvatarLoaderBase::SetExpression(FExpression ExpressionItem)
{
    //  APIEvents->OnItemClick();

    if (currentExpressionData.ID == ExpressionItem.ID)
    {
        ResetExpression();
        //
    }
    else
    {
        currentExpressionData = ExpressionItem;
        DataHolder->currentExpDataHolder = currentExpressionData;

        spawnedHeadActor->ClearAllBlendShape();
        if (ExpressionItem.BlendshapeKeys.blendShapes.Num() > 0)
        {
            for (int i = 0; i < ExpressionItem.BlendshapeKeys.blendShapes.Num(); i++)
            {
                FString shape = ExpressionItem.BlendshapeKeys.blendShapes[i].selectedShape;
                spawnedHeadActor->ChangeBlendshapeValue(shape, ExpressionItem.BlendshapeKeys.blendShapes[i].sliderValue);
            }
        }
    }

    APIEvents->OnItemClick();
}
void AAvatarLoaderBase::ResetExpression()
{
    spawnedHeadActor->ClearAllBlendShape();
    currentExpressionData = FExpression();
    DataHolder->currentExpDataHolder = currentExpressionData;
    APIEvents->OnUpdatexpPanelUI.Broadcast(true);
}

void AAvatarLoaderBase::ShowHideItems(bool show)
{
    if (show)
    {
        UE_LOG(LogTemp, Display, TEXT("THE AAvatarLoader  ShowItems-->>>>"));
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            UE_LOG(LogTemp, Display, TEXT("THE ACTOR NAMER -----%s"), *spawnedHeadActor->vertexPointsAdded[i]->BucketName);
            // spawnedHeadActor->vertexPointsAdded[i]->SetActorScale3D(FVector(1,1,1));
            spawnedHeadActor->vertexPointsAdded[i]->SetActorHiddenInGame(false);
        }
    }
    if (!show)
    {
        UE_LOG(LogTemp, Display, TEXT("THE AAvatarLoader  HideItems-->>>>"));
        // for (int i = 0; spawnedHeadActor->vertexPointsAdded.Num(); i++)
        // {
        //     UE_LOG(LogTemp, Display, TEXT("THE ACTOR-->>>>"));
        //     // UE_LOG(LogTemp,Display,TEXT("THE ACTOR NAMER -----%s"),*AvatarLoader->spawnedHeadActor->vertexPointsAdded[i]->BucketName);
        // }
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            UE_LOG(LogTemp, Display, TEXT("THE ACTOR NAMER -----%s"), *spawnedHeadActor->vertexPointsAdded[i]->BucketName);
            // spawnedHeadActor->vertexPointsAdded[i]->SetActorScale3D(FVector(0,0,0));
            spawnedHeadActor->vertexPointsAdded[i]->SetActorHiddenInGame(true);
        }
    }
}

void AAvatarLoaderBase::ShowClip(FClip clip)
{
    if (currentClip.ID == clip.ID)
    {
        // ResetExpression();
        currentClip = FClip();
    }
    else
    {
        currentClip = clip;
        ULoadTextureFromURL::LoadByte(clip.Artifacts.clips[0].url, FOnReceiveClipData);
    }
    APIEvents->UpdatesClipUI();
}
void AAvatarLoaderBase::ChangeBlendPointValue(FString Shapename, float Slidervalue)
{
    spawnedHeadActor->ChangeBlendshapeValue(Shapename, Slidervalue);
    if (SpawnedFacePoints.Num() > 0)
    {
        for (int i = 0; i < SpawnedFacePoints.Num(); i++)
        {
            float ForwardMovementValue = 0.5f;
            FVector ForwardVector = SpawnedFacePoints[i]->GetActorForwardVector();

            // Move the object forward by the desired value
            SpawnedFacePoints[i]->SetActorLocation(spawnedHeadActor->Locations[SpawnedFacePoints[i]->VertexNumber] + ForwardVector * ForwardMovementValue);
        }
    }
}

void AAvatarLoaderBase::LoadNetworkModel(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    networkModelQueue.Add(modelData);
    OnLoadQueModel();
}


void AAvatarLoaderBase::DelayFunction()
{
    if (isResetToCurrent)
    {
        isResetToCurrent = false;
    }
}

void AAvatarLoaderBase::ResetToDefaultData()
{
    AAvatarHandler *AvatarHandlerInstance = AAvatarHandler::GetInstance();
    if (AvatarHandlerInstance)
    {
        AvatarHandlerInstance->CurrentSelectedBodyParts.Empty();
    }
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HeadTattoo")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), DefaultEyebrowTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), DefaultLipsTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), DefaultFaceSkinTone);

    FLinearColor EyebrowColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultEyebrowColor, EyebrowColor);

    EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), DefaultEyeballTexture);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("EyebrowColor")), EyebrowColor);
    FLinearColor LipColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultLipColor, LipColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), LipColor);
    FLinearColor HairColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultHairColor, HairColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor")), HairColor);
    FLinearColor FacialColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultFacialHairColor, FacialColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("BeardColor")), FacialColor);

    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), DefaultBodySkinTone);

    UAvataryugData *AvataryugDataInstance = NewObject<UAvataryugData>(); // Create an instance
    TArray<FString> bodyTattoos = AvataryugDataInstance->bodytattos;     // Access the member

    for (int i = 0; i < bodyTattoos.Num(); i++)
    {
        BodyDynamicMaterial->SetTextureParameterValue(FName(bodyTattoos[i]), EmptyTexture);
    }
    lastLoadedTattoos.Empty();
    currentTopData = FEconomyItems();
    currentWristwearData = FEconomyItems();
    currentBottomData = FEconomyItems();
    currentOutfitData = FEconomyItems();
    currentFootwearData = FEconomyItems();
    currentHandwearData = FEconomyItems();
    currentLispData = FEconomyItems();
    currentfacialHairData = FEconomyItems();
    currentEyeballData = FEconomyItems();
    currentEyebrowData = FEconomyItems();
    currentHairData = FEconomyItems();
    currentHeadwearData = FEconomyItems();
    currentFaceshapeData = FEconomyItems();
    currentEarshapeData = FEconomyItems();
    currentNoseshapeData = FEconomyItems();
    currentEyebrowshapeData = FEconomyItems();
    currentEyeshapeData = FEconomyItems();
    currentLipshapeData = FEconomyItems();
    currentskintoneData = FEconomyItems();

    if (AvatarCurrentChangesInstance == nullptr)
    {
        AvatarCurrentChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
    }

    if (AvatarCurrentChangesInstance)
    {
        AvatarCurrentChangesInstance->changePropColors = FPropColors();
        AvatarCurrentChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();
        AvatarCurrentChangesInstance->changedProps = FProps();

        AvatarCurrentChangesInstance->changePropColors.EyebrowColor = DefaultEyebrowColor;
        AvatarCurrentChangesInstance->changePropColors.HairColor = DefaultHairColor;
        AvatarCurrentChangesInstance->changePropColors.FacialHairColor = DefaultFacialHairColor;
        AvatarCurrentChangesInstance->changePropColors.LipColor = DefaultLipColor;
    }
}



void AAvatarLoaderBase::DownloadTattos(FEconomyItems modelData)
{
    FString bucketName = GetBucketname(modelData.coreBucket);
    bool isPresentSameCat = false;
    bool isPresentLatstId = false;
    int tatooSameIDindex = -1;
    int tatooSameCatindex = -1;

    if (lastLoadedTattoos.Num() > 0)
    {
        for (int i = 0; i < lastLoadedTattoos.Num(); i++)
        {
            if (lastLoadedTattoos[i].ItemCategory == modelData.itemCategory)
            {
                isPresentSameCat = true;
                tatooSameCatindex = i;
                if (lastLoadedTattoos[i].tattooid == modelData.iD)
                {
                    isPresentLatstId = true;
                    tatooSameIDindex = i;
                }
            }
        }
    }

    bool addNew = false;

    if (isPresentSameCat)
    {
        if (isPresentLatstId)
        {
            DataHolder->RemovepropItem(modelData);
            lastLoadedTattoos.RemoveAt(tatooSameIDindex);
            OnProcessModelTexture();
            OnLoadQueModel();
        }
        else
        {
            DataHolder->RemovepropItem(modelData);
            lastLoadedTattoos.RemoveAt(tatooSameCatindex);
            OnProcessModelTexture();
            addNew = true;
        }
    }
    else
    {
        addNew = true;
    }

    if (addNew)
    {
        currentClickTatto = modelData;
        DataHolder->AddCurrenBodyPart(modelData);
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FTwoDArtifacts artifactlist;
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
        if(artifactlist.artifacts.Num() > 0)
        {
                FString Url = artifactlist.artifacts[0].url;
                ULoadTextureFromURL::LoadByte(Url, [this](UTexture2D *texture)
                {
                    FLoadedTattoo tatto;
                    tatto.ItemCategory = currentClickTatto.itemCategory;
                    tatto.tattooid = currentClickTatto.iD;
                    tatto.tattooTex = texture;
                    lastLoadedTattoos.Add(tatto);
                    OnProcessModelTexture();
                    OnLoadQueModel();                        
                }); 
        }
        else
        {
            OnProcessModelTexture();
            OnLoadQueModel();
        }
    }
}


FString AAvatarLoaderBase::GetBucketname(FString corebutckt)
{
    TArray<FString> buc;
    corebutckt.ParseIntoArray(buc, TEXT("/"), true);
    FString bucketname = buc[0];
    if (buc.Num() > 1)
    {
        bucketname = buc[1];
    }
    return bucketname;
}

void AAvatarLoaderBase::OnProcessModelTexture()
{

    // HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), texture);
    // spawnedHeadActor->SetBodyMaterial(BodyDynamicMaterial);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("LeftHandTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("RightHandTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("LeftFootTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("RightFootTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("FrontLeftLegTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("FrontLeftLegTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("FrontRightLegTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("LeftArmTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("RightArmTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("FrontBodyTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BackBodyTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BackRightLegTattoo")), EmptyTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BackLeftLegTattoo")), EmptyTexture);
    for (int i = 0; i < LoadedModelList.Num(); i++)
    {
        LoadedModelList[i]->SetBodyMaterial(BodyDynamicMaterial, "body");
    }

    if (HeadDynamicMaterial)
    {
        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HeadTattoo")), EmptyTexture);
    }
    spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);

    if (lastLoadedTattoos.Num() > 0)
    {
        for (int i = 0; i < lastLoadedTattoos.Num(); i++)
        {
            if (lastLoadedTattoos[i].ItemCategory == "HeadTattoo")
            {
                HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HeadTattoo")), lastLoadedTattoos[i].tattooTex);
            }
            else
            {

                BodyDynamicMaterial->SetTextureParameterValue(FName(lastLoadedTattoos[i].ItemCategory), lastLoadedTattoos[i].tattooTex);
            }
        }
    }
    spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
    for (int i = 0; i < LoadedModelList.Num(); i++)
    {
        LoadedModelList[i]->SetBodyMaterial(BodyDynamicMaterial, "body");
    }
}



void AAvatarLoaderBase::OnReceiveFaceModelData(TArray<uint8> byte)
{
    APIEvents->ShowLoading();
    TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
    FglTFRuntimeConfig runtimeConfig;
    runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
    UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
    if (!Asset)
    {
        return;
    }
    Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
    Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
    Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (BP_GltfActor != nullptr)
    {
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        GltfActor->Asset = Asset;
        GltfActor->LoadModel(currentClickEconomyItem.itemCategory);
        LoadedModelList.Add(GltfActor);
        LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                      { return Object == nullptr; });
        GltfActor->SetBodyMaterial(HairDynamicMaterial, "body");
        AddNetworkFacePart(GltfActor, currentClickEconomyItem);
    }
}

void AAvatarLoaderBase::OnReceiveModelBodywearData(TArray<uint8> byte)
{

    TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
    FglTFRuntimeConfig runtimeConfig;
    runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
    UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
    if (!Asset)
    {
        return;
    }
    Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
    Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
    Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (BP_GltfActor != nullptr)
    {

        UE_LOG(LogTemp, Display, TEXT("---BP_GltfActor---BYTEEE--2->>>"));
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        GltfActor->Asset = Asset;
        GltfActor->LoadModel(currentClickEconomyItem.itemCategory);
        LoadedModelList.Add(GltfActor);
        LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                      { return Object == nullptr; });
        AddNetworkBodywearPart(GltfActor, currentClickEconomyItem);
    }
}

void AAvatarLoaderBase::AddNetworkBodywearPart(AGltfActor *gltfActor, FEconomyItems modelData)
{
    FString bucketname = GetBucketname(modelData.coreBucket);
    FTimerHandle TimerHandle_Del;
    GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
    gltfActor->SetActorLocation(FVector(0, 0, 0));
    gltfActor->SetActorRotation(FRotator(0, 0, 0));
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    if (currentWristwearData.iD == modelData.iD)
    {

        if (currentWristwearActor != nullptr)
        {
            currentWristwearActor->Destroy();
        }
        currentWristwearData = FEconomyItems();
    }
    else
    {
        if (currentWristwearActor != nullptr)
        {
            currentWristwearActor->Destroy();
        }
        FName socketName = FName(bucketname);
        UE_LOG(LogTemp, Display, TEXT("---BP_GltfActor---socketName--->>> %s"), *bucketname);
        gltfActor->AttachToComponent(spawnedHeadActor->SkeletalHeadComponent, AttachmentTransformRules, socketName);
        gltfActor->SetActorRelativeScale3D(FVector(0.0100f, 0.0100f, 0.0100f));
        FString NewName = bucketname;
        // point->Rename(*NewName);
        // gltfActor->SetActorLabel(FString(bucketname + modelData.iD));
        gltfActor->nodeName = bucketname + modelData.iD;
        currentWristwearData = modelData;
        currentWristwearActor = gltfActor;
    }
    OnLoadQueModel();
}
void AAvatarLoaderBase::SpawnCustomizePoint(FFacePoint point)
{
    if (BP_CustomizeFacePoint != nullptr)
    {
        FActorSpawnParameters spawnparams;
        spawnparams.Owner = this;
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        ACustomizeFacePoint *facepoint = GetWorld()->SpawnActor<ACustomizeFacePoint>(BP_CustomizeFacePoint, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        // SpawnedHomeParent->AttachToActor(this, AttachmentTransformRules);
        SpawnedFacePoints.Add(facepoint);
        facepoint->AttachToActor(spawnedHeadActor, AttachmentTransformRules);
        facepoint->VertexNumber = point.VertexNumber;
        facepoint->partType = point.partType;
        facepoint->HorizontalShape = point.HorizontalShape;
        facepoint->VerticalShape = point.VerticalShape;
        facepoint->ViewDirection = point.ViewDirection;

        FString NewfacepointName =  point.VerticalShape + FString(TEXT("+")) +  point.HorizontalShape;
	    // facepoint->Rename(*NewfacepointName, nullptr, REN_Test);
        facepoint->PointsName = point.VerticalShape + "+" +  point.HorizontalShape;
        //facepoint->SetActorLabel( point.VerticalShape + "+" +  point.HorizontalShape);
        //facepoint->SetActorLabel(*NewfacepointName,true);
        // facepoint->Rename(*NewfacepointName, nullptr, REN_Test);
        // facepoint->SetActorLabel( point.VerticalShape + "+" +  point.HorizontalShape);
        // facepoint->SetActorLabel(*NewfacepointName,true);
        // facepoint->SetActorLocation();
        // facepoint->SetActorRotation(spawnedHeadActor->Locations[point.VertexNumber].Rotation());
        if (CameraControllerPaw != nullptr)
        {
            if (CameraControllerPaw->CameraComponent != nullptr)
            {
                FVector CameraPosition = CameraControllerPaw->CameraComponent->GetComponentLocation();
                FRotator LookAtRotation = FRotationMatrix::MakeFromX(CameraPosition - spawnedHeadActor->Locations[point.VertexNumber]).Rotator();
                facepoint->SetActorRotation(LookAtRotation);
            }
        }
        float ForwardMovementValue = 1;
        FVector ForwardVector = facepoint->GetActorForwardVector();

        // Move the object forward by the desired value
        facepoint->SetActorLocation(spawnedHeadActor->Locations[point.VertexNumber] + ForwardVector * ForwardMovementValue);
        // facepoint->SetActorRotation(LookAtRotation);
        // FVector WorldPosVertex = facepoint->GetTransform().TransformPosition(spawnedHeadActor->Locations[point.VertexNumber]);
        // FVector2D ViewportPos = UGameplayStatics::ProjectWorldToScreen(GetWorld(), WorldPosVertex);
        // facepoint->SetPosition(FVector2D(m_Rect->GetWidth() * ViewportPos.X, m_Rect->GetHeight() * ViewportPos.Y));
    };
}

void AAvatarLoaderBase::DestroySpawnCustomizePoint()
{
    for (int i = 0; i < SpawnedFacePoints.Num(); i++)
    {
        SpawnedFacePoints[i]->Destroy();
    }
    SpawnedFacePoints.Empty();
}

void AAvatarLoaderBase::ShowCustomizePoint(FString direction)
{
    for (int i = 0; i < SpawnedFacePoints.Num(); i++)
    {
        if (SpawnedFacePoints[i]->ViewDirection == direction)
        {
            SpawnedFacePoints[i]->SetActorEnableCollision(true);
            SpawnedFacePoints[i]->PlaneMesh->SetVisibility(true);
            SpawnedFacePoints[i]->SetActorHiddenInGame(false);
        }
        else
        {
            SpawnedFacePoints[i]->SetActorEnableCollision(false);
            SpawnedFacePoints[i]->PlaneMesh->SetVisibility(false);
            SpawnedFacePoints[i]->SetActorHiddenInGame(true);
        }
    }
}

void AAvatarLoaderBase::LoadBodywearPart(FEconomyItems modelData)
{
    currentClickEconomyItem = modelData;
    FString bucketName = GetBucketname(modelData.coreBucket);
    bool isModelPresent = false;

    if (modelData.itemCategory == "Wristwear")
    {
        if (currentWristwearData.iD == modelData.iD)
        {
            isModelPresent = true;
        }
    }
    if (isModelPresent)
    {
        if (currentWristwearActor != nullptr)
        {
            currentWristwearActor->Destroy();
        }
        currentWristwearData = FEconomyItems();
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
        OnLoadQueModel();
    }
    if (!isModelPresent)
    {
        FThreeDArtifacts artifacts;
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifacts,0,0);
        if (artifacts.artifacts.Num() > 0)
        {
            ULoadTextureFromURL::LoadByte(artifacts.artifacts[0].url,[this] (TArray<uint8> byte){
                TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
                FglTFRuntimeConfig runtimeConfig;
                runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
                UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
                if (!Asset)
                {
                    return;
                }
                Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
                Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
                Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

                FActorSpawnParameters spawnparams;
                spawnparams.Owner = this;
                if (BP_GltfActor != nullptr)
                {
                    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                    AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
                    GltfActor->Asset = Asset;
                    GltfActor->LoadModel(currentClickEconomyItem.itemCategory);
                    AddNetworkBodywearPart(GltfActor, currentClickEconomyItem);
                }
            });
        }
        else
        {
            FTimerHandle TimerHandle_Del;
            GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
             OnLoadQueModel();
        }
    }
}

bool AAvatarLoaderBase::IsBodyCategory(FEconomyItems modelData)
{
    bool isPresent = false;
    TArray<FString> Categorys = {"Top", "Bottom", "Outfit", "Handwear", "Footwear"};
    for (int i = 0; i < Categorys.Num(); i++)
    {
        if (Categorys[i] == modelData.itemCategory)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}

bool AAvatarLoaderBase::IsTattooCategory(FEconomyItems modelData)
{
    bool isPresent = false;
    TArray<FString> Categorys =
        {
            "LeftHandTattoo", "RightHandTattoo", "LeftFootTattoo", "RightFootTattoo",
            "FrontLeftLegTattoo", "FrontRightLegTattoo", "LeftArmTattoo", "RightArmTattoo",
            "BackBodyTattoo", "FrontBodyTattoo", "BackRightLegTattoo", "BackLeftLegTattoo", "HeadTattoo"};
    for (int i = 0; i < Categorys.Num(); i++)
    {
        if (Categorys[i] == modelData.itemCategory)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}

bool AAvatarLoaderBase::IsBlendshapeCategory(FEconomyItems modelData)
{
    bool isPresent = false;
    TArray<FString> Categorys = {"FaceShape", "EyeShape", "NoseShape", "EyebrowShape", "LipShape", "EarShape"};
    for (int i = 0; i < Categorys.Num(); i++)
    {
        if (Categorys[i] == modelData.itemCategory)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}

bool AAvatarLoaderBase::IsFace2DCategory(FEconomyItems modelData)
{
    bool isPresent = false;
    TArray<FString> Categorys = {"Eyebrow", "Eyeball", "Lips"};
    for (int i = 0; i < Categorys.Num(); i++)
    {
        if (Categorys[i] == modelData.itemCategory)
        {
            isPresent = true;
            break;
        }
    }
    return isPresent;
}



void AAvatarLoaderBase::OnReceiveModelByte(TArray<uint8> byte)
{
    TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
    FglTFRuntimeConfig runtimeConfig;
    runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
    UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
    if (!Asset)
    {
        return;
    }
    Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
    Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
    Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (BP_GltfActor != nullptr)
    {
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        GltfActor->Asset = Asset;
        GltfActor->LoadModel(currentClickEconomyItem.itemCategory);

        LoadedModelList.Add(GltfActor);
        LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                      { return Object == nullptr; });
        GltfActor->SetBodyMaterial(BodyDynamicMaterial, "body");
        AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));

        AvatarHandlerInstance->currentLoadEconomyItem = currentClickEconomyItem;
        AddNetworkBodyPart(GltfActor, currentClickEconomyItem);
        // currentClickEconomyItem = FEconomyItems();
    }
}

void AAvatarLoaderBase::AddNetworkFacePart(AGltfActor *gltfActor, FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    UE_LOG(LogTemp, Display, TEXT("AddNetworkFacePart--->>>HairModel    %s"), *modelData.itemCategory);
    //    bool isPrensent;
    FString bucketname = "";
    if (!modelData.coreBucket.IsEmpty())
    {
        bucketname = GetBucketname(modelData.coreBucket);
    }
    else
    {
        bucketname = "";
    }

    if(modelData.itemCategory == "Facialhair")
    {
        UE_LOG(LogTemp, Display, TEXT("--->>>Facial-HairModel<---- %s"), *modelData.itemCategory);
        // HairModel = gltfActor;
        gltfActor->SetBodyMaterial(HairDynamicMaterial,"Hair");
    }

    if (modelData.itemCategory == "Hair")
    {
        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
        spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
        UE_LOG(LogTemp, Display, TEXT("--->>>HairModel<---- %s"), *modelData.itemCategory);
        HairModel = gltfActor;
        gltfActor->SetBodyMaterial(HairDynamicMaterial, "Hair");

        if (HeadwearModel != nullptr)
        {
            // HeadCoreBuck = currentHeadwearData
            UE_LOG(LogTemp, Display, TEXT("--->>>HeadwearModel<--ot empty-- %s"), *HeadCoreBuck);
            // bool blendBucket = false;
            //  FName morphTargetName = FName(bucketname);
            if (HairModel->bothSkeletal.Num() > 0)
            {
                UE_LOG(LogTemp, Display, TEXT("--->>>HairModel->bothSkeletal<--ot empty-- %s"), *modelData.itemCategory);
                USkeletalMeshComponent *SkeletalMeshComponent = HairModel->bothSkeletal[0];
                SetBlendShapesWeight(SkeletalMeshComponent, HeadCoreBuck);
            }
        }
    }

    if (modelData.itemCategory == "Headwear")
    {
        HeadCoreBuck = GetBucketname(modelData.coreBucket);
        UE_LOG(LogTemp, Display, TEXT("ChangeBlendShapes--->>>bucketname    %s"), *bucketname);
        HeadwearModel = gltfActor;
        if (HairModel != nullptr)
        {
            // bool blendBucket = false;
            // FName morphTargetName = FName(bucketname);
            if (HairModel->bothSkeletal.Num() > 0)
            {
                USkeletalMeshComponent *SkeletalMeshComponent = HairModel->bothSkeletal[0];
                //  blendBucket = true;
                SetBlendShapesWeight(SkeletalMeshComponent, bucketname);
            }
            // if(HairModel->bothStatic.Num() > 0)
            // {
            //     UStaticMeshComponent* staticMeshComp = HairModel->bothStatic[0];
            // }
        }
    }
    UE_LOG(LogTemp, Display, TEXT("FAce--->>>bucketname    %s"), *bucketname);
    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        UE_LOG(LogTemp, Display, TEXT("FAce--->>>bucketname    %s"), *bucketname);
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
            {
                TArray<AActor *> AttachedActors;
                spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    UE_LOG(LogTemp, Display, TEXT("FAce--->>>AttachedActors[0]->Destroy    %s"), *bucketname);
                    AttachedActors[0]->Destroy();
                    // LoadedModelList.Remove(nullptr);
                }
            }
        }
    }
    if (modelData.conflictingBuckets.buckets.Num() > 0)
    {
        UE_LOG(LogTemp, Display, TEXT("FAce--->>>AttachedActors[0]->conflictingBuckets%s"), *bucketname);
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            for (int j = 0; j < modelData.conflictingBuckets.buckets.Num(); j++)
            {
                if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == modelData.conflictingBuckets.buckets[j].name)
                {
                    TArray<AActor *> AttachedActors;
                    spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                        AttachedActors[0]->Destroy();
                        // LoadedModelList.Remove(nullptr);
                    }
                }
            }
        }
    }

    AGltfStaticActorPoint *point = nullptr;
    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
            {
                point = spawnedHeadActor->vertexPointsAdded[i];
                break;
            }
        }
    }
    gltfActor->ID = modelData.iD;
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    gltfActor->AttachToActor(point, AttachmentTransformRules);
    if(bucketname == "face_full")
    {
        gltfActor->SetActorRelativeLocation(FVector(0, 1.5f, 0));
    }
    OnLoadQueModel();
}

void AAvatarLoaderBase::SetBlendShapesWeight(USkeletalMeshComponent *SkeletalMeshComponent, FString bucketname)
{
    // bool blendBucket = false;
    TMap<FName, int32> morphtargets = SkeletalMeshComponent->SkeletalMesh->GetMorphTargetIndexMap();
    for (TPair<FName, int32> Entry : morphtargets)
    {
        FString Key = Entry.Key.ToString();
        int32 Value = Entry.Value;
        UE_LOG(LogTemp, Warning, TEXT("Blend Shape Name: %s"), *Key);
        if (Key.Contains(bucketname))
        {
            UMorphTarget *morphTargetHead = SkeletalMeshComponent->FindMorphTarget(Entry.Key);
            if (morphTargetHead != nullptr)
            {
                // blendBucket = true;
                SkeletalMeshComponent->SetMorphTarget(Entry.Key, 1);
                UE_LOG(LogTemp, Warning, TEXT("SetMorphTarget--->>: %s"), *Key);
            }
        }

        // if(!blendBucket)
        // {
        //       USkeletalMeshComponent* SkMeshComponent = HairModel->bothSkeletal[0];
        //       SkMeshComponent->SetVisibility(false);

        // }
    }
}
void AAvatarLoaderBase::ResetBlendShapesWeight(USkeletalMeshComponent *SkeletalMeshComponent)
{
    TMap<FName, int32> morphtargets = SkeletalMeshComponent->SkeletalMesh->GetMorphTargetIndexMap();
    for (TPair<FName, int32> Entry : morphtargets)
    {
        FString Key = Entry.Key.ToString();
        int32 Value = Entry.Value;
        UE_LOG(LogTemp, Warning, TEXT("RESET Blend Shape Name: %s"), *Key);
        UMorphTarget *morphTargetHead = SkeletalMeshComponent->FindMorphTarget(Entry.Key);
        if (morphTargetHead != nullptr)
        {
            SkeletalMeshComponent->SetMorphTarget(Entry.Key, 0);
            UE_LOG(LogTemp, Warning, TEXT("RESET MorphTarget--->>: %s"), *Key);
        }
    }
}
void AAvatarLoaderBase::LoadDefaultModels()
{
    loadDefaultModellist.Empty();
    // EGender GenderValue = GetGender(); // Replace with your enum value
    FString gender;
    switch (UserDetailHolder->UserDetails.Gender)
    {
    case EGender::MALE:
        gender = "2";
        break;

    case EGender::FEMALE:
        gender = "1";
        break;
    }
    // Convert enum value to string
    // FString EnumAsString = UEnum::GetValueAsString(GenderValue);
    UE_LOG(LogTemp, Display, TEXT("GENDER VALUE--------->>%s"), *gender);
    TArray<FModelDataResponce> defaultModels = ULocalDataFunctionLibrary::GetDefaultModelList(gender);
    for (int i = 0; i < defaultModels.Num(); i++)
    {
        loadDefaultModellist.Add(defaultModels[i]);
        // OnLoadQueueDefaultModels();
    }
}

void AAvatarLoaderBase::LoadBlendshape(FEconomyItems modelData)
{
    FTimerHandle TimerHandle_Del;
    GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
    if (modelData.displayName == "Custom")
    {
        OnLoadQueModel();
    }
    else
    {
        if (modelData.itemCategory == "FaceShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Face_");
            if (currentFaceshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentFaceshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentFaceshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        if (modelData.itemCategory == "EyeShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Eyeshape_");
            spawnedHeadActor->ClearBlendShapeWithname("Iris");
            spawnedHeadActor->ClearBlendShapeWithname("Pupil");
            if (currentEyeshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentEyeshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentEyeshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        if (modelData.itemCategory == "EyebrowShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Eyebrows_");
            if (currentEyebrowshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentEyebrowshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentEyebrowshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        if (modelData.itemCategory == "NoseShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Nose_");
            if (currentNoseshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentNoseshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentNoseshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        if (modelData.itemCategory == "LipShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Lips_");
            if (currentLipshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentLipshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentLipshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        if (modelData.itemCategory == "EarShape")
        {
            spawnedHeadActor->ClearBlendShapeWithname("Ears_");
            if (currentLipshapeData.iD == modelData.iD)
            {
                DataHolder->RemovepropItem(modelData);
                currentEarshapeData = FEconomyItems();
            }
            else
            {
                DataHolder->AddCurrenBodyPart(modelData);
                currentEarshapeData = modelData;
                for (size_t i = 0; i < modelData.blendshapeKeys.blendShapes.Num(); i++)
                {
                    spawnedHeadActor->ChangeBlendshapeValue(modelData.blendshapeKeys.blendShapes[i].shapekeys, modelData.blendshapeKeys.blendShapes[i].sliderValue);
                }
            }
        }
        OnLoadQueModel();
    }
}

void AAvatarLoaderBase::LoadHead2dCategory(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    if (modelData.itemCategory == "Eyeball")
    {
        bool addnew = true;
        if (currentEyeballData.iD == modelData.iD)
        {
            currentEyeballData = FEconomyItems();
            if (EyeballDynamicMaterial != nullptr && DefaultEyeballTexture != nullptr)
            {
                EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), DefaultEyeballTexture);
            }
            spawnedHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
            addnew = false;
            DataHolder->RemovepropItem(modelData);
            OnLoadQueModel();
        }
        if (addnew)
        {
            DataHolder->AddCurrenBodyPart(modelData);
            currentEyeballData = modelData;
            FString artifactString = "{";
            artifactString.Append("\"artifacts\":");
            artifactString.Append(modelData.artifacts);
            artifactString.Append("}");
            FTwoDArtifacts artifactlist;
            FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
            if(artifactlist.artifacts.Num() > 0)
            {
                FString Url = artifactlist.artifacts[0].url;
                ULoadTextureFromURL::LoadByte(Url, [this](UTexture2D *texture)
                                                                          {
                    EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), texture);
                    spawnedHeadActor->SetEyeMaterial(EyeballDynamicMaterial);
                    OnLoadQueModel();                        
                }); 
            }
            else
            {
                OnLoadQueModel();
            }
        }
    }
    if (modelData.itemCategory == "Lips")
    {
        bool addnew = true;
        if (currentLispData.iD == modelData.iD)
        {
            currentLispData = FEconomyItems();
            if (DefaultLipsTexture != nullptr && HeadDynamicMaterial != nullptr)
            {
                HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), DefaultLipsTexture);
            }
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            addnew = false;
            DataHolder->RemovepropItem(modelData);
            OnLoadQueModel();
        }
        if (addnew)
        {
            DataHolder->AddCurrenBodyPart(modelData);
            currentLispData = modelData;
            FString artifactString = "{";
            artifactString.Append("\"artifacts\":");
            artifactString.Append(modelData.artifacts);
            artifactString.Append("}");
            FTwoDArtifacts artifactlist;
            FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);

            if(artifactlist.artifacts.Num() > 0)
            {
                FString Url = artifactlist.artifacts[0].url;
                ULoadTextureFromURL::LoadByte(Url, [this](UTexture2D *texture)
                                                                          {
                    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), texture);
                    spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
                    OnLoadQueModel();                     
                }); 
            }
            else
            {
                OnLoadQueModel();
            }
        }
    }
    if (modelData.itemCategory == "Eyebrow")
    {
        bool addnew = true;
        if (currentEyebrowData.iD == modelData.iD)
        {
            currentEyebrowData = FEconomyItems();
            if (HeadDynamicMaterial != nullptr && DefaultEyebrowTexture != nullptr)
            {
                HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), DefaultEyebrowTexture);
            }
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            addnew = false;
            DataHolder->RemovepropItem(modelData);
            OnLoadQueModel();
        }
        if (addnew)
        {
            DataHolder->AddCurrenBodyPart(modelData);
            currentEyebrowData = modelData;
            FString artifactString = "{";
            artifactString.Append("\"artifacts\":");
            artifactString.Append(modelData.artifacts);
            artifactString.Append("}");
            FTwoDArtifacts artifactlist;
            FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
            if(artifactlist.artifacts.Num() > 0)
            {
                FString Url = artifactlist.artifacts[0].url;
                ULoadTextureFromURL::LoadByte(Url, [this](UTexture2D *texture)
                                                                          {
                   HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), texture);
                    spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
                    OnLoadQueModel();                    
                }); 
            }
            else
            {
                OnLoadQueModel();
            }
          
        }
    }
}



void AAvatarLoaderBase::OnReceiveHairTexture(UTexture *texture)
{
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), texture);
    spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
    OnLoadQueModel();
}



void AAvatarLoaderBase::LoadFaceAccessary(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    UE_LOG(LogTemp, Display, TEXT("LoadFaceAccessaryr----->>> %s"), *modelData.itemCategory);
    if (modelData.itemCategory == "Hair" || modelData.itemCategory == "Headwear")
    {
        if (HairModel != nullptr)
        {
            if (HairModel->bothSkeletal.Num() > 0)
            {
                UE_LOG(LogTemp, Display, TEXT("HairModel --SkeletalMeshComponent --->>>"));
                USkeletalMeshComponent *SkeletalMeshComponent = HairModel->bothSkeletal[0];
                ResetBlendShapesWeight(SkeletalMeshComponent);
            }
        }
    }
    if (modelData.itemCategory == "Hair")
    {
        currentHairData = modelData;
    }
    currentClickEconomyItem = modelData;
    FString bucketname = GetBucketname(modelData.coreBucket);
    bool isModelPresent = false;
    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            // spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname;
            TArray<AActor *> AttachedActors;
            spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() > 0)
            {
                AGltfActor *MyCastActor = Cast<AGltfActor>(AttachedActors[0]);
                if (MyCastActor)
                {
                    UE_LOG(LogTemp, Display, TEXT("LoadFaceAccessary GLTF ACTOR ---->>> %s"), *MyCastActor->ID);
                    if (MyCastActor->ID.Contains(modelData.iD))
                    {
                        isModelPresent = true;
                                    AttachedActors[0]->Destroy();
                                    APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);

                        FTimerHandle TimerHandle_Del;
                        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
                        DataHolder->RemovepropItem(modelData);

                        break;
                    }
                }
            }
        }
    }
    if (isModelPresent)
    {
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
        if (modelData.itemCategory == "Headwear")
        {

            UE_LOG(LogTemp, Display, TEXT("isModel Headwear ----->>>"));
            if (HairModel != nullptr)
            {
                if (HairModel->bothSkeletal.Num() > 0)
                {
                    UE_LOG(LogTemp, Display, TEXT("isModel HairModel --SkeletalMeshComponent --->>>"));
                    USkeletalMeshComponent *SkeletalMeshComponent = HairModel->bothSkeletal[0];
                    ResetBlendShapesWeight(SkeletalMeshComponent);
                }
            }
            //   HeadCoreBuck = "";
            // ResetBlendshapes();
        }
        DataHolder->RemovepropItem(modelData);
    }
    if (!isModelPresent)
    {
        UE_LOG(LogTemp, Display, TEXT("isModelPresent is NOT ----->>>"));
        if (spawnedHeadActor != nullptr)
        {
            for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
            {
                for (int j = 0; j < modelData.conflictingBuckets.buckets.Num(); j++)
                {
                    if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == modelData.conflictingBuckets.buckets[j].name)
                    {
                        TArray<AActor *> AttachedActors;
                        spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (attachedActor)
                            {
                                attachedActor->Destroy();
                                APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                                if (bucketname.ToLower().Contains("hair"))
                                {
                                    // HeadMaterial.SetTexture("_HairTexture", avatarLocalData.empty);
                                    HairDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
                                }
                            }
                        }
                    }
                }
                if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
                {
                    TArray<AActor *> AttachedActors;
                    spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                        AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                        if (attachedActor)
                        {
                                 attachedActor->Destroy();
                                   APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                            if (bucketname.ToLower().Contains("hair"))
                            {
                                HairDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
                            }
                        }
                    }
                }
            }
        }

        DataHolder->AddCurrenBodyPart(modelData);
        APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
        FThreeDArtifacts artifacts;
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");

        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifacts,0,0);
        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(artifactString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            if (JsonObject->HasField(TEXT("artifacts")))
            {
                TArray<TSharedPtr<FJsonValue>> ArtifactArray = JsonObject->GetArrayField(TEXT("artifacts"));
                if (ArtifactArray.Num() > 0)
                {
                    TSharedPtr<FJsonObject> FirstArtifactObject = ArtifactArray[0]->AsObject();
                    if (FirstArtifactObject.IsValid() && FirstArtifactObject->HasField(TEXT("url")))
                    {
                        FString Url = FirstArtifactObject->GetStringField(TEXT("url"));
                        // Now, 'Url' contains the URL string from the first item in the array.
                        // You can use it as needed.
                        // For example, you can print it to the log:
                        UE_LOG(LogTemp, Warning, TEXT("First Face Item URL: %s"), *Url);
                        APIEvents->ShowLoading();
                        ULoadTextureFromURL::LoadByte(Url, FOnReceiveFaceModelData);
                    }
                }
            }
        }
        else
        {
            // Handle JSON parsing error if needed
        }
    }
}

void AAvatarLoaderBase::ResetToDetaultModel()
{
    ResetToDefault([this](){

    });
}

void AAvatarLoaderBase::ResetToCurrentSelected()
{
    ResetToCurrentSelectedModel([this](){});
}

void AAvatarLoaderBase::ResetToCurrentSelectedModel()
{
    isResetToCurrent = true;
    ResetToDefault([this]
                   {

        networkModelQueue.Empty();
        AAvatarHandler* AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));
        ACurrentAvatarChanges* AvatarChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
        if(AvatarChangesInstance)
        {
            UE_LOG(LogTemp,Display,TEXT("AvatarChangesInstance--PRESENTSs-->>>"));
            AvatarChangesInstance->changePropColors.HairColor = AvatarChangesInstance->currentpropColors.HairColor;
            AvatarChangesInstance->changePropColors.FacialHairColor = AvatarChangesInstance->currentpropColors.FacialHairColor;
            AvatarChangesInstance->changePropColors.LipColor = AvatarChangesInstance->currentpropColors.LipColor;
            AvatarChangesInstance->changePropColors.EyebrowColor = AvatarChangesInstance->currentpropColors.EyebrowColor;
            AvatarChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();

            for (int i = 0; i < AvatarChangesInstance->currentBlendShapes.Num(); i++)
            {
            if(AvatarHandlerInstance)
            {
                 UE_LOG(LogTemp,Display,TEXT("AvatarHandler--PRESENTSs-->>>"));
                spawnedHeadActor->ChangeBlendshapeValue(AvatarChangesInstance->currentBlendShapes[i].shapekeys,AvatarChangesInstance->currentBlendShapes[i].value);
                AvatarChangesInstance->changeBlendShapes.Add(AvatarChangesInstance->currentBlendShapes[i]);
            }
            }
            for (int i = 0; i < AvatarChangesInstance->currentProps.props.Num(); i++)
            {
                FEconomyItems Item = EconomyItemHolder->GetEconomyItemWithId(AvatarChangesInstance->currentProps.props[i].ID);
                networkModelQueue.Add(Item);
            }

            OnLoadQueModel();

        } });
}

void AAvatarLoaderBase::ResetToCurrentMaterial()
{
    FLinearColor EyebrowColora;
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("EyebrowColor")), EyebrowColora);

    AAvatarHandler *AvatarInstance = AAvatarHandler::GetInstance();
    FLinearColor col = FLinearColor::Red;
    switch (GetGender())
    {
    case EGender::MALE:
        UAvataryugFunctionLibrary::HexToLinearColor(DefaultLipColor, col);
        HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), col);
        break;

    case EGender::FEMALE:
        UAvataryugFunctionLibrary::HexToLinearColor(DefaultLipColor, col);
        HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), col);
        break;
    }
    FLinearColor Color;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultHairColor, Color);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor")), Color);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HeadTattoo")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), DefaultEyebrowTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), DefaultLipsTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), DefaultFaceSkinTone);

    EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), DefaultEyeballTexture);
    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), DefaultBodySkinTone);

    UAvataryugData *AvataryugDataInstance = NewObject<UAvataryugData>(); // Create an instance
    TArray<FString> bodyTattoos = AvataryugDataInstance->bodytattos;     // Access the member

    for (int i = 0; i < bodyTattoos.Num(); i++)
    {
        BodyDynamicMaterial->SetTextureParameterValue(FName(bodyTattoos[i]), EmptyTexture);
    }
    FLinearColor EyebrowColor;
    UAvataryugFunctionLibrary::HexToLinearColor(AvatarCurrentChangesInstance->changePropColors.EyebrowColor, EyebrowColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("EyebrowColor")), EyebrowColor);
    FLinearColor LipColor;
    UAvataryugFunctionLibrary::HexToLinearColor(AvatarCurrentChangesInstance->changePropColors.LipColor, LipColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), LipColor);
    FLinearColor HairColor;
    UAvataryugFunctionLibrary::HexToLinearColor(AvatarCurrentChangesInstance->changePropColors.HairColor, HairColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor")), HairColor);

    for (const FProp &item : AvatarCurrentChangesInstance->currentProps.props)
    {
        FEconomyItems itemData;
        itemData = EconomyItemHolder->GetEconomyCurrentItemWithId(item.ID);
        AvatarInstance->AddCurrentBodyPart(itemData);
        FCurrentEconomyItemTexture texData;
        texData = EconomyItemHolder->GetCurrentEconomyTex(texData.ID);
        if (itemData.itemCategory == "SkinTone")
        {
            HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), texData.texture1);
            BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), texData.texture2);
        }

        // UAvataryugData* AvataryugDataInstance = NewObject<UAvataryugData>(); // Create an instance
        // TArray<FString> bodyTattoos = AvataryugDataInstance->bodytattos; // Access the member

        if (AvataryugDataInstance->IsBodyTattooCategory(itemData.itemCategory))
        {
            BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), texData.texture1);
        }
        if (AvataryugDataInstance->IsHead2DCategoty(itemData.itemCategory))
        {
            if (itemData.itemCategory == "Eyeball")
            {
                EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), texData.texture1);
            }
            if (itemData.itemCategory == "Lips")
            {
                HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), texData.texture1);
            }
            if (itemData.itemCategory == "Eyebrow")
            {
                HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), texData.texture1);
            }
        }
        if (AvataryugDataInstance->IsHeadCategoty(itemData.itemCategory))
        {
            if (itemData.itemCategory == "Hair")
            {
                if (itemData.config.isTwoD == 1)
                {
                    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), texData.texture1);
                }
            }
            if (itemData.itemCategory == "Facialhair")
            {
                if (itemData.config.isTwoD == 1)
                {
                    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), texData.texture1);
                }
            }
        }
    }
}

void AAvatarLoaderBase::SetBodyPartColor(FLinearColor OutColor, FString category)
{
    UE_LOG(LogTemp, Display, TEXT("Set BodyPart Color VALUE---BY FIXED------>>%s"), *category);
    outColor = OutColor;
    tempcat = OutColor;
    FString hexColor = "";
    UAvataryugFunctionLibrary::LinearColorToHex(OutColor,hexColor);
    if (spawnedHeadActor != nullptr)
    {
        if (category == "Hair")
        {
            UE_LOG(LogTemp, Display, TEXT("Set BodyPart Color VALUE---BY FIXED---222--->>%s"), *category);
            HairDynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor")), OutColor);
            // HairModel->SetMaterial(0,HairDynamicMaterial);
            if(HairModel != nullptr)
            HairModel->SetBodyMaterial(HairDynamicMaterial, category);

            AvatarCurrentChangesInstance->changePropColors.HairColor = hexColor;
        }
        if (category == "Facialhair")
        {
            HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("BeardColor")), OutColor);
            AvatarCurrentChangesInstance->changePropColors.FacialHairColor= hexColor;
        }
        if (category == "Eyebrow")
        {
            HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("EyebrowColor")), OutColor);
              AvatarCurrentChangesInstance->changePropColors.EyebrowColor = hexColor;
        }
        if (category == "Lips")
        {
            HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), OutColor);
              AvatarCurrentChangesInstance->changePropColors.LipColor= hexColor;
        }
        spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
    }
}

void AAvatarLoaderBase::ResetData()
{
    if (AvatarCurrentChangesInstance == nullptr)
    {
        AvatarCurrentChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
        AvatarCurrentChangesInstance->changedProps = FProps();

        for (int i = 0; i < AvatarCurrentChangesInstance->currentProps.props.Num(); i++)
        {
            FProp tempItem = AvatarCurrentChangesInstance->currentProps.props[i];
            AvatarCurrentChangesInstance->changedProps.props.Add(tempItem);
        }

        AvatarCurrentChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();

        for (int i = 0; i < AvatarCurrentChangesInstance->currentBlendShapes.Num(); i++)
        {
            AvatarCurrentChangesInstance->changeBlendShapes.Add(AvatarCurrentChangesInstance->currentBlendShapes[i]);
        }

        FString col = AvatarCurrentChangesInstance->currentpropColors.HairColor;
        AvatarCurrentChangesInstance->changePropColors.HairColor = col;

        col = AvatarCurrentChangesInstance->currentpropColors.FacialHairColor;
        AvatarCurrentChangesInstance->changePropColors.FacialHairColor = col;

        col = AvatarCurrentChangesInstance->currentpropColors.LipColor;
        AvatarCurrentChangesInstance->changePropColors.LipColor = col;

        col = AvatarCurrentChangesInstance->currentpropColors.EyebrowColor;
        AvatarCurrentChangesInstance->changePropColors.EyebrowColor = col;

        currentTopData = FEconomyItems();
        currentWristwearData = FEconomyItems();
        currentBottomData = FEconomyItems();
        currentOutfitData = FEconomyItems();
        currentFootwearData = FEconomyItems();
        currentHandwearData = FEconomyItems();
        currentLispData = FEconomyItems();
        currentfacialHairData = FEconomyItems();
        currentEyeballData = FEconomyItems();
        currentEyebrowData = FEconomyItems();
        currentHairData = FEconomyItems();
        currentHeadwearData = FEconomyItems();
        currentFaceshapeData = FEconomyItems();
        currentEarshapeData = FEconomyItems();
        currentNoseshapeData = FEconomyItems();
        currentEyebrowshapeData = FEconomyItems();
        currentEyeshapeData = FEconomyItems();
        currentLipshapeData = FEconomyItems();
        currentskintoneData = FEconomyItems();
    }
}

void AAvatarLoaderBase::ResetToDefault(TFunction<void()> complete)
{
    AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));
    if (AvatarHandlerInstance)
    {
        UE_LOG(LogTemp, Display, TEXT("AvatarHandler--RESET-TO-DEFAULT--CurrentSelectedBodyParts-->>>"));
        AvatarHandlerInstance->CurrentSelectedBodyParts.Empty();
    }

    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HeadTattoo")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), EmptyTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyebrowTexture")), DefaultEyebrowTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("LipsTexture")), DefaultLipsTexture);
    HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), DefaultFaceSkinTone);
   
    FLinearColor EyebrowColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultEyebrowColor, EyebrowColor);

    EyeballDynamicMaterial->SetTextureParameterValue(FName(TEXT("EyeTexture")), DefaultEyeballTexture);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("EyebrowColor")), EyebrowColor);
    FLinearColor LipColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultLipColor, LipColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("LipsColor")), LipColor);
    FLinearColor HairColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultHairColor, HairColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("HairColor")), HairColor);
    FLinearColor FacialColor;
    UAvataryugFunctionLibrary::HexToLinearColor(DefaultFacialHairColor, FacialColor);
    HeadDynamicMaterial->SetVectorParameterValue(FName(TEXT("BeardColor")), FacialColor);

    BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), DefaultBodySkinTone);

    UAvataryugData *AvataryugDataInstance = NewObject<UAvataryugData>(); // Create an instance
    TArray<FString> bodyTattoos = AvataryugDataInstance->bodytattos;     // Access the member
    if (spawnedHeadActor != nullptr)
    {
        spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
        spawnedHeadActor->ClearAllBlendShape();
    }
    for (int i = 0; i < bodyTattoos.Num(); i++)
    {
        BodyDynamicMaterial->SetTextureParameterValue(FName(bodyTattoos[i]), EmptyTexture);
    }
    lastLoadedTattoos.Empty();
    currentTopData = FEconomyItems();
    currentWristwearData = FEconomyItems();
    currentBottomData = FEconomyItems();
    currentOutfitData = FEconomyItems();
    currentFootwearData = FEconomyItems();
    currentHandwearData = FEconomyItems();
    currentLispData = FEconomyItems();
    currentfacialHairData = FEconomyItems();
    currentEyeballData = FEconomyItems();
    currentEyebrowData = FEconomyItems();
    currentHairData = FEconomyItems();
    currentHeadwearData = FEconomyItems();
    currentFaceshapeData = FEconomyItems();
    currentEarshapeData = FEconomyItems();
    currentNoseshapeData = FEconomyItems();
    currentEyebrowshapeData = FEconomyItems();
    currentEyeshapeData = FEconomyItems();
    currentLipshapeData = FEconomyItems();
    currentskintoneData = FEconomyItems();

    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            TArray<AActor *> AttachedActors;
            spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() > 0)
            {
                        AttachedActors[0]->Destroy();
            }
        }
    }


    if (AvatarCurrentChangesInstance == nullptr)
    {
        AvatarCurrentChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
    }

    // AvatarCurrentChangesInstance->changePropColors.Empty();
    if (AvatarCurrentChangesInstance)
    {
        UE_LOG(LogTemp, Display, TEXT("AvatarCurrentChangesInstance--PRESENT---->>>"));
        AvatarCurrentChangesInstance->changePropColors = FPropColors();
        AvatarCurrentChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();
        AvatarCurrentChangesInstance->changedProps = FProps();

        AvatarCurrentChangesInstance->changePropColors.EyebrowColor = DefaultEyebrowColor;
        AvatarCurrentChangesInstance->changePropColors.HairColor = DefaultHairColor;
        AvatarCurrentChangesInstance->changePropColors.FacialHairColor = DefaultFacialHairColor;
        AvatarCurrentChangesInstance->changePropColors.LipColor = DefaultLipColor;
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("AvatarCurrentChangesInstance--NO PRESENT---->>>"));
    }
    DataHolder->currentSelectedBodyParts.Empty();
    if (bodyPoints.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            TArray<AActor *> AttachedActors;
            bodyPoints[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() == 0)
            {
            }
            if (AttachedActors.Num() > 0)
            {
                AttachedActors[0]->Destroy();
                LoadedModelList.Remove(nullptr);
                bodyPoints.RemoveAt(i);
            }
        }
    }

    loadDefaultModellist.Empty();
    // EGender GenderValue = GetGender(); // Replace with your enum value
    FString gender;
    switch (UserDetailHolder->UserDetails.Gender)
    {
    case EGender::MALE:
        gender = "2";
        break;

    case EGender::FEMALE:
        gender = "1";
        break;
    }
    UE_LOG(LogTemp, Display, TEXT("GENDER VALUE--------->>%s"), *gender);
    TArray<FModelDataResponce> defaultModels = ULocalDataFunctionLibrary::GetDefaultModelList(gender);
    for (int i = 0; i < defaultModels.Num(); i++)
    {
        loadDefaultModellist.Add(defaultModels[i]);
    }
    OnLoadQueueDefaultModel([this, complete]
                            { complete(); });
}

void AAvatarLoaderBase::OnLoadQueueDefaultModel(TFunction<void()> OnComplete)
{
    if (loadDefaultModellist.Num() == 0)
    {
        APIEvents->HideLoading();
        OnComplete();
    }
    else
    {
        APIEvents->ShowLoading();
        modelDataRes = loadDefaultModellist[0];
        loadDefaultModellist.RemoveAt(0);
        DownloadDefaultModel(modelDataRes, OnComplete);
    }
}

void AAvatarLoaderBase::DownloadDefaultModel(FModelDataResponce modelData, TFunction<void()> OnComplete)
{
    APIEvents->ShowLoading();
    FglTFRuntimeConfig runtimeConfig;
    runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
    FJsonSerializableKeyValueMap headers;
    ULoadTextureFromURL::LoadByte(modelData.data.GlbPath, [this, OnComplete](TArray<uint8> result)
                                  {
                                      FglTFRuntimeConfig runtimeConfig;
                                      runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
                                      UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
                                      if (!Asset)
                                      {
                                          return;
                                      }
                                      Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
                                      Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
                                      Asset->LoadFromData(result.GetData(), result.Num(), runtimeConfig);

                                        FActorSpawnParameters spawnparams;
                                        spawnparams.Owner = this;
                                        if (BP_GltfActor != nullptr)
                                        {
                                            const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                                            AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
                                            GltfActor->Asset = Asset;
                                            GltfActor->LoadModel(modelDataRes.data.MainCatID);

                                            LoadedModelList.Add(GltfActor);
                                            LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                                                          { return Object == nullptr; });
                                            GltfActor->SetBodyMaterial(BodyDynamicMaterial, "body");
                                            AddNewDefaultBodyPart(GltfActor, modelDataRes, [this, OnComplete]
                                                                  { OnLoadQueueDefaultModel([this, OnComplete]
                                                                                            { OnComplete(); }); });
                                        } });
}
void AAvatarLoaderBase::AddNewDefaultBodyPart(AGltfActor *gltfActor, FModelDataResponce modelDataResponce, TFunction<void()> OnComplete)
{
    UE_LOG(LogTemp, Display, TEXT("<---AddNewDefaultBodyPart MODEL--->>%s"), *modelDataResponce.data.MainCatID);
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    int index = 0;

    TArray<FString> buckets = UKismetStringLibrary::ParseIntoArray(modelDataResponce.data.CoreBucket, TEXT("/"), true);
    FString bucketname = buckets[0];

    if (buckets.Num() > 1)
    {
        bucketname = buckets[1];
    }
    AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));

    if (bodyPoints.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (bodyPoints[i]->BucketName == bucketname)
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    AttachedActors[0]->Destroy();
                }
            }
        }
    }

    if (!modelDataRes.data.ConflictingBuckets.IsEmpty())
    {
        FConflictList ConflictList;
        FJsonObjectConverter::JsonObjectStringToUStruct(modelDataResponce.data.ConflictingBuckets, &ConflictList,0,0);
        for (int k = 0; k < ConflictList.conflits.Num(); k++)
        {
            for (int j = 0; j < bodyPoints.Num(); j++)
            {
                if (bodyPoints[j]->BucketName == ConflictList.conflits[k].name)
                {
                    TArray<AActor *> AttachedActors;
                    bodyPoints[j]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                        AttachedActors[0]->Destroy();
                    }
                }
            }
        }
    }
    bool isPresent = false;
    AGltfStaticActorPoint *bodyPoint = nullptr;
    if (bodyPoints.Num() > 0)
    {
        for (AGltfStaticActorPoint *item : bodyPoints)
        {
            if (item->BucketName == bucketname)
            {
                UE_LOG(LogTemp, Display, TEXT("<---bodyPoints----BucketName--->>%s"), *bucketname);
                bodyPoint = item;
                isPresent = true;
                break;
            }
        }
    }

    if (!isPresent)
    {

        bodyPoint = GetWorld()->SpawnActor<AGltfStaticActorPoint>(BucketPoint_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        bodyPoint->BucketName = bucketname;
        FString NewbodyPointName = bucketname;
        //  bodyPoint->SetActorLabel(bucketname);
        bodyPoint->AttachToActor(this, AttachmentTransformRules);
        bodyPoints.Add(bodyPoint);
    }
    const FAttachmentTransformRules AttachmentTransformRuler = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    gltfActor->AttachToActor(bodyPoint, AttachmentTransformRuler);
    FString NewgvxName = modelDataResponce.data.MainCatID;
    
    UE_LOG(LogTemp, Display, TEXT("<---COmpleted MODEL--->>"));
    FTimerHandle TimerHandle_Del;
    GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 1.0f, false);

    OnComplete();
}

void AAvatarLoaderBase::ResetToCurrentSelectedModel(TFunction<void()> Oncomplete)
{
    isResetToCurrent = true;
    ResetToDefault([this]
                   {
                        networkModelQueue.Empty();
                        AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));
                        ACurrentAvatarChanges *AvatarChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
                        if (AvatarChangesInstance)
                        {
                            AvatarChangesInstance->changePropColors.HairColor = AvatarChangesInstance->currentpropColors.HairColor;
                            AvatarChangesInstance->changePropColors.FacialHairColor = AvatarChangesInstance->currentpropColors.FacialHairColor;
                            AvatarChangesInstance->changePropColors.LipColor = AvatarChangesInstance->currentpropColors.LipColor;
                            AvatarChangesInstance->changePropColors.EyebrowColor = AvatarChangesInstance->currentpropColors.EyebrowColor;
                            AvatarChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();

                           for (int i = 0; i < AvatarChangesInstance->currentBlendShapes.Num(); i++)
                           {
                               if (AvatarHandlerInstance)
                               {
                                   spawnedHeadActor->ChangeBlendshapeValue(AvatarChangesInstance->currentBlendShapes[i].shapekeys, AvatarChangesInstance->currentBlendShapes[i].value);
                                   AvatarChangesInstance->changeBlendShapes.Add(AvatarChangesInstance->currentBlendShapes[i]);
                               }
                           }

                           if (AvatarChangesInstance->currentProps.props.Num() > 0)
                           {
                               for (int i = 0; i < AvatarChangesInstance->currentProps.props.Num(); i++)
                               {
                                   FEconomyItems Item = EconomyItemHolder->GetEconomyItemWithId(AvatarChangesInstance->currentProps.props[i].ID);
                                   networkModelQueue.Add(Item);
                               }
                                  OnLoadQueModel();
                           }
                       } 
        });
}

void AAvatarLoaderBase::OnLoadQueModel()
{
    APIEvents->ShowLoading();
    if (networkModelQueue.Num() > 0)
    {
        FEconomyItems tempModelData = networkModelQueue[0];
        networkModelQueue.RemoveAt(0);
        DownloadNetworkModel(tempModelData);
        AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));
        AvatarHandlerInstance->CurrentSelectedProp = tempModelData;
    }
    else
    {
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 1.0f, false);
        FTimerHandle TimerHandle_DelayedCall;
        GetWorldTimerManager().SetTimer(TimerHandle_DelayedCall, this, &AAvatarLoaderBase::DelayFunction, 1.0f, false);
    }
}
void AAvatarLoaderBase::DownloadNetworkModel(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    DataHolder->currentSelectedBodyPart = modelData;
    if (modelData.itemCategory == "SkinTone")
    {
        LoadSkinTone(modelData);
    }
    else if (IsFace2DCategory(modelData))
    {
        LoadHead2dCategory(modelData);
    }
    else if (IsTattooCategory(modelData))
    {
        DownloadTattos(modelData);
    }
    else if (IsBlendshapeCategory(modelData))
    {
        LoadBlendshape(modelData);
    }
    else if (modelData.itemCategory == "Wristwear")
    {
        LoadBodywearPart(modelData);
    }
    else if (IsBodyCategory(modelData))
    {
        LoadBodyPart(modelData);
    }else if( modelData.itemCategory == "Facialhair")
    {
        LoadFacialHair(modelData, [this]() {});
    }
    else if (modelData.itemCategory == "Hair"  || 
    modelData.itemCategory == "Headwear" || modelData.itemCategory == "Eyewear" || 
    modelData.itemCategory == "Mouthwear" || modelData.itemCategory == "Earwear" || 
    modelData.itemCategory == "Eyebrowswear" || modelData.itemCategory == "Facewear" || 
    modelData.itemCategory == "Neckwear" || modelData.itemCategory == "Nosewear")
    {
        if(modelData.itemCategory == "Hair" &&  modelData.config.isTwoD == 1)
        {
            UE_LOG(LogTemp, Display, TEXT("Loading TWOD HAIR PART---->>"));
            LoadTwoDHair(modelData,[this](){
                APIEvents->HideLoading();   
            });
        }
        else
        {
          UE_LOG(LogTemp, Display, TEXT("Loading 3D HAIR PART---->>"));
          LoadFaceAccessary(modelData);
        }
    }
    else
    {
        OnLoadQueModel();
    }
}
void AAvatarLoaderBase::LoadTwoDHair(FEconomyItems modelData,TFunction<void()> complete)
{
    APIEvents->ShowLoading();
    currentClickEconomyItem = modelData;
    FString bucketname = GetBucketname(modelData.coreBucket);
    bool isModelPresent = false;
    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            TArray<AActor *> AttachedActors;
            spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() > 0)
            {
             
                AGltfActor *MyCastActor = Cast<AGltfActor>(AttachedActors[0]);
                if (MyCastActor)
                {
                    if (MyCastActor->ID.Contains(modelData.iD))
                    {
                        isModelPresent = true;
                        AttachedActors[0]->Destroy();
                        break;
                    }
                }
            }
        }
    }
    if (isModelPresent)
    {
        DataHolder->RemovepropItem(modelData);
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
     
            HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), EmptyTexture);
            if (spawnedHeadActor != nullptr)
            {
                spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
            }
        OnLoadQueModel();
    }
    else
    {
        if (spawnedHeadActor != nullptr)
        {
            for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
            {
                for (int j = 0; j < modelData.conflictingBuckets.buckets.Num(); j++)
                {
                    if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == modelData.conflictingBuckets.buckets[j].name)
                    {
                        TArray<AActor *> AttachedActors;
                        spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (attachedActor)
                            {
                                attachedActor->Destroy();
                                APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                            }
                        }
                    }
                }
                if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
                {
                    TArray<AActor *> AttachedActors;
                    spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                        AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                        if (attachedActor)
                        {
                            attachedActor->Destroy();
                            APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                        }
                    }
                }
            }
        }

        DataHolder->AddCurrenBodyPart(modelData);
        APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
        FThreeDArtifacts artifacts;
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifacts,0,0);
        if (artifacts.artifacts.Num() > 0)
        {
            ULoadTextureFromURL::LoadByte(artifacts.artifacts[0].url,[this,modelData,bucketname,complete](TArray<uint8> byte){
            TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
            FglTFRuntimeConfig runtimeConfig;
            runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
            UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
            if (!Asset)
            {
                return;
            }
            Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
            Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
            Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

            FActorSpawnParameters spawnparams;
            spawnparams.Owner = this;
            if (BP_GltfActor != nullptr)
            {
                const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
                GltfActor->Asset = Asset;
                AGltfStaticActorPoint *point = nullptr;
                if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
                {
                    for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
                    {
                        if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
                        {
                            point = spawnedHeadActor->vertexPointsAdded[i];
                            break;
                        }
                    }
                }
                GltfActor->ID = modelData.iD;
                GltfActor->LoadModel(currentClickEconomyItem.itemCategory);
                GltfActor->AttachToActor(point, AttachmentTransformRules);
                if (modelData.config.isTwoD == 1)
                {
                    GltfActor->SetActorHiddenInGame(true);
                    FString artifactString = "https://aystorage.b-cdn.net/files/diffuse/";
                    artifactString.Append(modelData.templateId);
                    artifactString.Append(".png");
                     ULoadTextureFromURL::LoadByte(artifactString, [this](UTexture2D *texture)
                    {
                        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("HairTexture")), texture);
                        if (spawnedHeadActor != nullptr)
                        {
                            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
                             APIEvents->HideLoading();
                        }
                    }); 
                }
                else
                {
                    OnLoadQueModel();
                    complete();
                }
            }
            });
        }
        else
        {
            OnLoadQueModel();
        }
    }
}

void AAvatarLoaderBase::LoadFacialHair(FEconomyItems modelData,TFunction<void()> complete)
{
    APIEvents->ShowLoading();
    currentClickEconomyItem = modelData;
    FString bucketname = GetBucketname(modelData.coreBucket);
    bool isModelPresent = false;
    if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
    {
        for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
        {
            TArray<AActor *> AttachedActors;
            spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
            if (AttachedActors.Num() > 0)
            {
             
                AGltfActor *MyCastActor = Cast<AGltfActor>(AttachedActors[0]);
                if (MyCastActor)
                {
                    if (MyCastActor->ID.Contains(modelData.iD))
                    {
                        isModelPresent = true;
                        AttachedActors[0]->Destroy();
                        break;
                    }
                }
            }
        }
    }
    UTexture* tempTexture;
    if (HeadDynamicMaterial->GetTextureParameterValue(FName(TEXT("FacialHairTexture")), tempTexture))
    {
        if (tempTexture != EmptyTexture)
        {
            HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), EmptyTexture);
        }
    }
    if (isModelPresent)
    {
        DataHolder->RemovepropItem(modelData);
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), EmptyTexture);
        if (spawnedHeadActor != nullptr)
        {
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
        }
        OnLoadQueModel();
    }
    else
    {
        if (spawnedHeadActor != nullptr)
        {
            for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
            {
                for (int j = 0; j < modelData.conflictingBuckets.buckets.Num(); j++)
                {
                    if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == modelData.conflictingBuckets.buckets[j].name)
                    {
                        TArray<AActor *> AttachedActors;
                        spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (attachedActor)
                            {
                                attachedActor->Destroy();
                                APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                            }
                        }
                    }
                }
                if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
                {
                    TArray<AActor *> AttachedActors;
                    spawnedHeadActor->vertexPointsAdded[i]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                        AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                        if (attachedActor)
                        {
                            attachedActor->Destroy();
                            APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
                        }
                    }
                }
            }
        }

        DataHolder->AddCurrenBodyPart(modelData);
        APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
        FThreeDArtifacts artifacts;
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifacts,0,0);
        if (artifacts.artifacts.Num() > 0)
        {
            ULoadTextureFromURL::LoadByte(artifacts.artifacts[0].url,[this,modelData,bucketname,complete](TArray<uint8> byte){
            TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
            FglTFRuntimeConfig runtimeConfig;
            runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
            UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
            if (!Asset)
            {
                return;
            }
            Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
            Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
            Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

            FActorSpawnParameters spawnparams;
            spawnparams.Owner = this;
            if (BP_GltfActor != nullptr)
            {
                const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
                GltfActor->Asset = Asset;
                AGltfStaticActorPoint *point = nullptr;
                if (spawnedHeadActor->vertexPointsAdded.Num() > 0)
                {
                    for (int i = 0; i < spawnedHeadActor->vertexPointsAdded.Num(); i++)
                    {
                        if (spawnedHeadActor->vertexPointsAdded[i]->BucketName == bucketname)
                        {
                            point = spawnedHeadActor->vertexPointsAdded[i];
                            break;
                        }
                    }
                }
                GltfActor->ID = modelData.iD;
                GltfActor->LoadModel(currentClickEconomyItem.itemCategory);
                GltfActor->AttachToActor(point, AttachmentTransformRules);
                if (modelData.config.isTwoD == 1)
                {
                    GltfActor->SetActorHiddenInGame(true);
                    FString artifactString = "https://aystorage.b-cdn.net/files/diffuse/";
                    artifactString.Append(modelData.templateId);
                    artifactString.Append(".png");
                    ULoadTextureFromURL::LoadByte(artifactString, [this](UTexture2D *texture)
                    {
                        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FacialHairTexture")), texture);
                        if (spawnedHeadActor != nullptr)
                        {
                            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
                              APIEvents->HideLoading();   
                              OnLoadQueModel();

                        }
                     }); 
                }
                else
                {
                    OnLoadQueModel();
                    complete();
                }
            }
            });
        }
        else
        {
            OnLoadQueModel();
        }
    }
}

void AAvatarLoaderBase::LoadSkinTone(FEconomyItems modelData)
{
    if (currentskintoneData.iD == modelData.iD)
    {
        APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(false);
        currentskintoneData = FEconomyItems();
        DataHolder->RemovepropItem(modelData);
        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), DefaultFaceSkinTone);
        BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), DefaultBodySkinTone);
        if (spawnedHeadActor != nullptr)
        {
            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
        }
        for (int i = 0; i < LoadedModelList.Num(); i++)
        {
            LoadedModelList[i]->SetBodyMaterial(BodyDynamicMaterial, "body");
        }
        FTimerHandle TimerHandle_Del;
        GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::AddLoadingDelay, 2.0f, false);
        OnLoadQueModel();
    }
    else
    {
        currentskintoneData = modelData;
        DataHolder->AddCurrenBodyPart(modelData);
        FSkinToneArtifacts artifactlist;
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
        if (artifactlist.artifacts.Num() > 0)
        {
            ULoadTextureFromURL::LoadByte(artifactlist.artifacts[0].face_path, [this, artifactlist](UTexture2D *faceTex)
                { ULoadTextureFromURL::LoadByte(artifactlist.artifacts[0].body_path, [this, faceTex](UTexture2D *bodyTex)
                {
                        HeadDynamicMaterial->SetTextureParameterValue(FName(TEXT("FaceTexture")), faceTex);
                        BodyDynamicMaterial->SetTextureParameterValue(FName(TEXT("BodyTexture")), bodyTex);
                        if (spawnedHeadActor != nullptr)
                        {
                            spawnedHeadActor->SetBodyMaterial(HeadDynamicMaterial);
                        }
                        for (int i = 0; i < LoadedModelList.Num(); i++)
                        {
                            LoadedModelList[i]->SetBodyMaterial(BodyDynamicMaterial, "body");
                        }
                        OnLoadQueModel(); }); });
        }
        APIEvents->UpdatesHeadUI();
        APIEvents->OnUpdateHeadCatBuyButtonUI.Broadcast(true);
    }
}

void AAvatarLoaderBase::LoadBodyPart(FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));
    currentClickEconomyItem = modelData;
    AvatarHandlerInstance->currentLoadEconomyItem = currentClickEconomyItem;
    FString bucketName = "";
    if (!modelData.coreBucket.IsEmpty())
    {
        bucketName = GetBucketname(modelData.coreBucket);
    }
    bool isModelPresent = false;
    if (modelData.itemCategory == "Top")
    {
        if (currentTopData.iD == modelData.iD)
        {
            if (bodyPoints.Num() > 0)
            {
                for (int i = 0; i < bodyPoints.Num(); i++)
                {
                    if (bodyPoints[i]->BucketName == bucketName)
                    {
                        TArray<AActor *> AttachedActors;
                        bodyPoints[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            FString atta = "";
                            AGltfActor *CustomActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (CustomActor)
                            {
                                FString MainCategory = CustomActor->MainCategory;
                                // Now you can use the MainCategory as needed
                                UE_LOG(LogTemp, Warning, TEXT("MainCategory: %s"), *MainCategory);
                                atta = MainCategory;
                            }
                            // atta = AttachedActors[0]->GetActorLabel();
                            UE_LOG(LogTemp, Display, TEXT("Checking AttachedActors Default PART---->>%s"), *atta);
                            for (int j = 0; j < LoadedModelList.Num(); j++)
                            {
                                FString nam = LoadedModelList[j]->MainCategory;
                                if (!nam.IsEmpty())
                                {
                                    if (nam == atta)
                                    {
                                        UE_LOG(LogTemp, Display, TEXT("DESTROYING AttachedActors Default PART---->>%s"), *atta);
                                        LoadedModelList.RemoveAt(j);
                                        AttachedActors[0]->Destroy();
                                        
                                        // LoadedModelList.Remove(AttachedActors[0]);
                                    }
                                }
                            }
                            APIEvents->OnUpdateBuyButtonUI.Broadcast(false);
                            isModelPresent = true;
                            DataHolder->RemovepropItem(modelData);
                            currentTopData = FEconomyItems();
                            CheckMissingModelAfterRemovingSameModel(modelData);
                        }
                    }
                }
            }
            currentTopData = FEconomyItems();
        }
        else
        {
            DataHolder->AddCurrenBodyPart(modelData);
            DataHolder->RemovepropItemWithCat("Outfit");
            APIEvents->OnUpdateBuyButtonUI.Broadcast(true);
            currentTopData = modelData;
            currentOutfitData = FEconomyItems();
        }
    }
    if (modelData.itemCategory == "Bottom")
    {
        if (currentBottomData.iD == modelData.iD)
        {
            if (bodyPoints.Num() > 0)
            {
                for (int i = 0; i < bodyPoints.Num(); i++)
                {
                    if (bodyPoints[i]->BucketName == bucketName)
                    {
                        TArray<AActor *> AttachedActors;
                        bodyPoints[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            FString atta = "";
                            AGltfActor *CustomActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (CustomActor)
                            {
                                FString MainCategory = CustomActor->MainCategory;
                                // Now you can use the MainCategory as needed
                                UE_LOG(LogTemp, Warning, TEXT("Bottom--->>Category: %s"), *MainCategory);
                                atta = MainCategory;
                            }
                            // atta = AttachedActors[0]->GetActorLabel();
                            UE_LOG(LogTemp, Display, TEXT("Checking AttachedActors Default Bottom PART---->>%s"), *atta);
                            for (int j = 0; j < LoadedModelList.Num(); j++)
                            {
                                FString nam = LoadedModelList[j]->MainCategory;
                                if (!nam.IsEmpty())
                                {
                                    if (nam == atta)
                                    {
                                        UE_LOG(LogTemp, Display, TEXT("DESTROYING BOTTOM  PART---->>%s"), *atta);
                                        LoadedModelList.RemoveAt(j);
                                        AttachedActors[0]->Destroy();
                                        APIEvents->OnUpdateBuyButtonUI.Broadcast(false);
                                        // LoadedModelList.Remove(AttachedActors[0]);
                                    }
                                }
                            }
                            // AttachedActors[0]->Destroy();
                            // LoadedModelList.Remove(nullptr);
                            isModelPresent = true;
                            DataHolder->RemovepropItem(modelData);
                            // APIEvents->OnPropButtonClick(false);
                            currentBottomData = FEconomyItems();
                            CheckMissingModelAfterRemovingSameModel(modelData);
                        }
                    }
                }
            }
            AAvatarHandler *HandlerInstance = AAvatarHandler::GetInstance();
            // HandlerInstance->RemovePart(currentBottomData);
            currentBottomData = FEconomyItems();
        }
        else
        {
            DataHolder->AddCurrenBodyPart(modelData);
            DataHolder->RemovepropItemWithCat("Outfit");
            APIEvents->OnUpdateBuyButtonUI.Broadcast(true);
            currentBottomData = modelData;
            addDelay = false;
            // APIEvents->OnPropButtonClick(true);

            currentOutfitData = FEconomyItems();
        }
    }
    if (modelData.itemCategory == "Outfit")
    {
        UE_LOG(LogTemp, Display, TEXT("Checking if ITEMS is  Outfit---->>%s"), *modelData.displayName);
        if (currentOutfitData.iD == modelData.iD)
        {
            UE_LOG(LogTemp, Display, TEXT("Checking currentOutfitData---->>%s"), *modelData.displayName);
            if (bodyPoints.Num() > 0)
            {
                for (int i = 0; i < bodyPoints.Num(); i++)
                {
                    if (bodyPoints[i]->BucketName == bucketName)
                    {
                        UE_LOG(LogTemp, Display, TEXT("bucketName Available---->>%s"), *bucketName);
                        TArray<AActor *> AttachedActors;
                        bodyPoints[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            FString atta = "";
                            AGltfActor *CustomActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (CustomActor)
                            {
                                FString MainCategory = CustomActor->MainCategory;
                                // Now you can use the MainCategory as needed
                                UE_LOG(LogTemp, Warning, TEXT("Bottom--->>Category: %s"), *MainCategory);
                                atta = MainCategory;
                            }
                            // atta = AttachedActors[0]->GetActorLabel();
                            UE_LOG(LogTemp, Display, TEXT("Checking AttachedActors OUTFIT PART---->>%s"), *atta);
                            for (int j = 0; j < LoadedModelList.Num(); j++)
                            {
                                FString nam = LoadedModelList[j]->MainCategory;
                                if (!nam.IsEmpty())
                                {
                                    if (nam == atta)
                                    {
                                        UE_LOG(LogTemp, Display, TEXT("DESTROYING OUTFIT  PART---->>%s"), *atta);
                                        AttachedActors[0]->Destroy();
                                        LoadedModelList.RemoveAt(j);
                                        APIEvents->OnUpdateBuyButtonUI.Broadcast(false);
                                        // LoadedModelList.Remove(AttachedActors[0]);
                                    }
                                }
                            }
                            UE_LOG(LogTemp, Display, TEXT("Default item is present---->>%s"), *bucketName);
                            // AttachedActors[0]->Destroy();
                            // LoadedModelList.Remove(nullptr);
                            isModelPresent = true;
                            DataHolder->RemovepropItem(modelData);
                            APIEvents->OnPropButtonClick(false);
                            currentOutfitData = FEconomyItems();
                            CheckMissingModelAfterRemovingSameModel(modelData);
                        }
                    }
                }
            }

            // HandlerInstance->RemovePart(currentOutfitData);
            currentOutfitData = FEconomyItems();
        }
        else
        {
            UE_LOG(LogTemp, Warning, TEXT("ELSE----->>>Checking Adding OUTFIT DAta PART---->>%s"), *modelData.iD);

            DataHolder->AddCurrenBodyPart(modelData);
            /* if(AvatarHandlerInstance)
               {
                    if (AvatarHandlerInstance->customizeAvatarLoader->bodyPoints.Num() > 0)
                    {
                        for (int i = 0; i < AvatarHandlerInstance->customizeAvatarLoader->bodyPoints.Num(); i++)
                        {
                            if (AvatarHandlerInstance->customizeAvatarLoader->bodyPoints[i]->BucketName == bucketName)
                            {
                                UE_LOG(LogTemp,Warning,TEXT("bucketName Available---->>%s"),*bucketName);
                                TArray<AActor *> AttachedActors;
                                AvatarHandlerInstance->customizeAvatarLoader->bodyPoints[i]->GetAttachedActors(AttachedActors);
                                if (AttachedActors.Num() > 0)
                                {
                                    FString atta = AttachedActors[0]->GetActorLabel();
                                    UE_LOG(LogTemp,Warning,TEXT("Checking AttachedActors OUTFIT PART---->>%s"),*atta);
                                    for (int j = 0; j < LoadedModelList.Num(); j++)
                                    {
                                        FString nam = LoadedModelList[j]->MainCategory;
                                        if(!nam.IsEmpty())
                                        {
                                            if(nam == atta)
                                            {
                                                UE_LOG(LogTemp,Warning,TEXT("DESTROYING OUTFIT  PART---->>%s"),*atta);
                                                LoadedModelList.RemoveAt(j);
                                                AttachedActors[0]->Destroy();
                                                // LoadedModelList.Remove(AttachedActors[0]);
                                            }
                                        }
                                    }
                                    UE_LOG(LogTemp,Warning,TEXT("Default item is present---->>%s"),*bucketName);
                                    // AttachedActors[0]->Destroy();
                                    // LoadedModelList.Remove(nullptr);
                                    isModelPresent = true;

                                }
                            }
                        }
                    }
                }*/
            DataHolder->RemovepropItemWithCat("Top");
            DataHolder->RemovepropItemWithCat("Bottom");
            currentOutfitData = modelData;
            APIEvents->OnPropButtonClick(true);
            currentTopData = FEconomyItems();
            currentBottomData = FEconomyItems();
            addDelay = true;
            APIEvents->OnUpdateBuyButtonUI.Broadcast(true);
            // if (modelData.ConflictingBuckets.buckets.Find(f => f.name == "lowerbody_foot_both") != null)
            // {
            //  DataHolder->RemovepropItemWithCat("Footwear");
            // }
            // if (modelData.conflictingBuckets.buckets.ContainsByPredicate([](const FBucket& Bucket)
            // {
            //     return Bucket.name == TEXT("lowerbody_foot_both");
            // }))
            // {
            //     // HandlerInstance->RemovePart()
            //     // Assuming DataHolder is a pointer to an object that has a RemovepropItemWithCat function.
            //     DataHolder->RemovepropItemWithCat(TEXT("Footwear"));
            // }
        }
    }
    if (modelData.itemCategory == "Footwear")
    {
        if (currentFootwearData.iD == modelData.iD)
        {
            if (bodyPoints.Num() > 0)
            {
                for (int i = 0; i < bodyPoints.Num(); i++)
                {
                    if (bodyPoints[i]->BucketName == bucketName)
                    {
                        TArray<AActor *> AttachedActors;
                        bodyPoints[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            FString atta = "";
                            AGltfActor *CustomActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (CustomActor)
                            {
                                FString MainCategory = CustomActor->MainCategory;
                                // Now you can use the MainCategory as needed
                                UE_LOG(LogTemp, Warning, TEXT("Footwear--->>Category: %s"), *MainCategory);
                                atta = MainCategory;
                            }
                            UE_LOG(LogTemp, Display, TEXT("Checking AttachedActors Default PART---->>%s"), *atta);
                            for (int j = 0; j < LoadedModelList.Num(); j++)
                            {
                                FString nam = LoadedModelList[j]->MainCategory;
                                if (!nam.IsEmpty())
                                {
                                    if (nam == atta)
                                    {
                                        UE_LOG(LogTemp, Display, TEXT("DESTROYING Footwear  PART---->>%s"), *atta);
                                        LoadedModelList.RemoveAt(j);
                                        AttachedActors[0]->Destroy();
                                        APIEvents->OnUpdateBuyButtonUI.Broadcast(false);
                                        // LoadedModelList.Remove(AttachedActors[0]);
                                    }
                                }
                            }
                            // AttachedActors[0]->Destroy();
                            // // LoadedModelList.Remove(nullptr);
                            isModelPresent = true;
                            DataHolder->RemovepropItem(modelData);
                            APIEvents->OnPropButtonClick(false);
                            currentFootwearData = FEconomyItems();
                            CheckMissingModelAfterRemovingSameModel(modelData);
                        }
                    }
                }
            }

            // HandlerInstance->RemovePart(currentFootwearData);
            currentFootwearData = FEconomyItems();
        }
        else
        {
            DataHolder->AddCurrenBodyPart(modelData);
            currentFootwearData = modelData;
            APIEvents->OnPropButtonClick(true);
            APIEvents->OnUpdateBuyButtonUI.Broadcast(true);
        }
    }
    if (modelData.itemCategory == "Handwear")
    {
        if (currentHandwearData.iD == modelData.iD)
        {
            if (bodyPoints.Num() > 0)
            {
                for (int i = 0; i < bodyPoints.Num(); i++)
                {
                    if (bodyPoints[i]->BucketName == bucketName)
                    {
                        TArray<AActor *> AttachedActors;
                        bodyPoints[i]->GetAttachedActors(AttachedActors);
                        if (AttachedActors.Num() > 0)
                        {
                            AGltfActor *attachedActor = Cast<AGltfActor>(AttachedActors[0]);
                            if (attachedActor)
                            {
                                FString atta = attachedActor->MainCategory;
                                for (int j = 0; j < LoadedModelList.Num(); j++)
                                {
                                    AGltfActor *loadedModel = Cast<AGltfActor>(LoadedModelList[j]);
                                    if (loadedModel)
                                    {
                                        if (loadedModel->MainCategory == atta)
                                        {
                                            UE_LOG(LogTemp, Display, TEXT("DESTROYING Footwear  PART---->>%s"), *atta);
                                            LoadedModelList.RemoveAt(j);
                                            attachedActor->Destroy();
                                            APIEvents->OnUpdateBuyButtonUI.Broadcast(false);
                                        }
                                    }
                                }
                                isModelPresent = true;
                                DataHolder->RemovepropItem(modelData);
                                APIEvents->OnPropButtonClick(false);
                                currentHandwearData = FEconomyItems();
                                CheckMissingModelAfterRemovingSameModel(modelData);
                            }
                        }
                    }
                }
            }
            AAvatarHandler *HandlerInstance = AAvatarHandler::GetInstance();
            // HandlerInstance->RemovePart(currentHandwearData);
            currentHandwearData = FEconomyItems();
        }
        else
        {
            DataHolder->AddCurrenBodyPart(modelData);
            APIEvents->OnPropButtonClick(true);
            currentHandwearData = modelData;
            APIEvents->OnUpdateBuyButtonUI.Broadcast(true);
        }
    }

    if (!isModelPresent)
    {
        FString artifactString = "{";
        artifactString.Append("\"artifacts\":");
        artifactString.Append(modelData.artifacts);
        artifactString.Append("}");
        FThreeDArtifacts ThreeDartifacts;
        FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &ThreeDartifacts,0,0);
        UE_LOG(LogTemp, Display, TEXT("LoadArtifact  %s"), *artifactString);

        TSharedPtr<FJsonObject> JsonObject;
        TSharedRef<TJsonReader<TCHAR>> JsonReader = TJsonReaderFactory<TCHAR>::Create(artifactString);

        if (FJsonSerializer::Deserialize(JsonReader, JsonObject))
        {
            if (JsonObject->HasField(TEXT("artifacts")))
            {
                TArray<TSharedPtr<FJsonValue>> ArtifactArray = JsonObject->GetArrayField(TEXT("artifacts"));
                if (ArtifactArray.Num() > 0)
                {
                    TSharedPtr<FJsonObject> FirstArtifactObject = ArtifactArray[0]->AsObject();
                    if (FirstArtifactObject.IsValid() && FirstArtifactObject->HasField(TEXT("url")))
                    {
                        FString Url = FirstArtifactObject->GetStringField(TEXT("url"));
                        UE_LOG(LogTemp, Warning, TEXT("First URL: %s"), *Url);
                        ULoadTextureFromURL::LoadByte(Url,[this] (TArray<uint8> byte){
                         TArray<uint8> modedata = ULoadTextureFromURL::GetModelByte(byte);
    FglTFRuntimeConfig runtimeConfig;
    runtimeConfig.TransformBaseType = EglTFRuntimeTransformBaseType::YForward;
    UglTFRuntimeAsset *Asset = NewObject<UglTFRuntimeAsset>();
    if (!Asset)
    {
        return;
    }
    Asset->RuntimeContextObject = runtimeConfig.RuntimeContextObject;
    Asset->RuntimeContextString = runtimeConfig.RuntimeContextString;
    Asset->LoadFromData(modedata.GetData(), modedata.Num(), runtimeConfig);

    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;
    if (BP_GltfActor != nullptr)
    {
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        AGltfActor *GltfActor = GetWorld()->SpawnActor<AGltfActor>(BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        GltfActor->Asset = Asset;
        GltfActor->LoadModel(currentClickEconomyItem.itemCategory);

        LoadedModelList.Add(GltfActor);
        LoadedModelList.RemoveAllSwap([](AGltfActor *Object)
                                      { return Object == nullptr; });
        GltfActor->SetBodyMaterial(BodyDynamicMaterial, "body");
        AAvatarHandler *AvatarHandlerInstance = Cast<AAvatarHandler>(UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass()));

        AvatarHandlerInstance->currentLoadEconomyItem = currentClickEconomyItem;
        AddNetworkBodyPart(GltfActor, currentClickEconomyItem);
    }
                                });





                    }
                }
            }
        }
    }else{
         OnLoadQueModel();
    }
}

void AAvatarLoaderBase::AddNetworkBodyPart(AGltfActor *gltfActor, FEconomyItems modelData)
{
    APIEvents->ShowLoading();
    FString bucketname = "";
    bucketname = GetBucketname(modelData.coreBucket);

    if (bodyPoints.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (bodyPoints[i]->BucketName == bucketname)
            {
                TArray<AActor *> AttachedActors;
                bodyPoints[i]->GetAttachedActors(AttachedActors);
                if (AttachedActors.Num() > 0)
                {
                    AttachedActors[0]->Destroy();
                }
            }
        }
    }


    if (modelData.conflictingBuckets.buckets.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            for (int j = 0; j < modelData.conflictingBuckets.buckets.Num(); j++)
            {
                if (bodyPoints[i]->BucketName == modelData.conflictingBuckets.buckets[j].name)
                {
                    TArray<AActor *> AttachedActors;
                    bodyPoints[i]->GetAttachedActors(AttachedActors);
                    if (AttachedActors.Num() > 0)
                    {
                         AttachedActors[0]->Destroy();
                    }
                }
            }
        }
    }
    LoadedModelList.RemoveAllSwap([](AGltfActor *Object)    { return Object == nullptr; });
    bool isPrensent = false;
    AGltfStaticActorPoint *point = nullptr;
    if (bodyPoints.Num() > 0)
    {
        for (int i = 0; i < bodyPoints.Num(); i++)
        {
            if (bodyPoints[i]->BucketName == bucketname)
            {
                isPrensent = true;
                point = bodyPoints[i];
                break;
            }
        }
    }

    if (!isPrensent)
    {
        FActorSpawnParameters spawnparams;
        spawnparams.Owner = this;
        point = GetWorld()->SpawnActor<AGltfStaticActorPoint>(BucketPoint_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
        point->BucketName = bucketname;
        FString NewName = bucketname;
        const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        point->AttachToActor(this, AttachmentTransformRules);
        bodyPoints.Add(point);
    }
    gltfActor->ID = modelData.iD;
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    gltfActor->AttachToActor(point, AttachmentTransformRules);
     OnLoadQueModel();
    CheckMissingAfterModelLoad(modelData);
}