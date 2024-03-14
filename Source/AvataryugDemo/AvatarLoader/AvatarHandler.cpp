// Fill out your copyright notice in the Description page of Project Settings.

#include "AvatarHandler.h"
#include "Kismet/GameplayStatics.h"
#include "../DataHolders/CurrentAvatarChanges.h"
#include "EconomyAPI/EconomyHandler.h"
#include "EconomyAPI/EconomyRequest.h"
#include "EconomyAPI/EconomyModel.h"
#include "TimerManager.h"
#include "../DataHolders/AvataryugData.h"

AAvatarHandler *AAvatarHandler::SingletonInstance = nullptr;
// Sets default values
AAvatarHandler::AAvatarHandler()
{
    // Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.

    // if (SingletonInstance)
    // {
    //     // If an instance already exists, destroy this one
    //     Destroy();
    //     return;
    // }

    // // Set the Singleton instance to this instance
    // SingletonInstance = this;

    PrimaryActorTick.bCanEverTick = true;
}
UFUNCTION()

AAvatarHandler *AAvatarHandler::GetInstance()
{
    return SingletonInstance;
}

// Called when the game starts or when spawned
void AAvatarHandler::BeginPlay()
{
    Super::BeginPlay();

    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
    }
    //  AExponentialHeightFog* Fog = World->SpawnActor<AExponentialHeightFog>();

    if (Foger == nullptr)
    {
        Foger = GetWorld()->SpawnActor<AExponentialHeightFog>();

        // Foger->FogDensityColor = FLinearColor(0.0f, 0.0f, 0.2f);
        // Set the new Fog Inscattering Color (dark blue)
        // Foger->InscatteringColor = FLinearColor(0.0f, 0.0f, 0.2f); // Dark blue
        // Note: You should have a reference to the Exponential Height Fog component,
        // either by finding it in the level or through a reference in your class.
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

    if (AvatarChangesInstance == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        AvatarChangesInstance = Cast<ACurrentAvatarChanges>(FoundActor);
        if (AvatarChangesInstance == nullptr)
        {
            AvatarChangesInstance = GetWorld()->SpawnActor<ACurrentAvatarChanges>();
        }
    }
    if (CommonFunctionHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
        CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);

        if (CommonFunctionHolder == nullptr)
        {
            CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
        }
        // AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        // CommonFunctionHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        //  CurrentAvatarChangesHolder->SetActorLabel(FString("CurrentAvatarChangesHolder"));
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

    APIEvents->OnSetModelParentDelegate.RemoveDynamic(this, &AAvatarHandler::SetModelParentEnable);
    APIEvents->OnSetModelParentDelegate.AddDynamic(this, &AAvatarHandler::SetModelParentEnable);
    APIEvents->OnResetToDefault.BindUObject(this, &AAvatarHandler::ApiEvents_ResetToDefault);
    OnGetEconomyItemsByIDResult.BindUFunction(this, "GetEconomyItemsByIDReply");
    OnGetEconomyItemsByIDError.BindUFunction(this, "GetEconomyItemsByIDApiError");
    OnGetEconomyItemsResult.BindUFunction(this, "OnReceiveEconomyItems");
    OnGetEconomyItemsError.BindUFunction(this, "OnReceiveEconomyItemsError");
    LoadParents();

      APIEvents->OnHorizontalInput.RemoveDynamic(this, &AAvatarHandler::OnGetHorizontalInput);
    APIEvents->OnHorizontalInput.AddDynamic(this, &AAvatarHandler::OnGetHorizontalInput);

    APIEvents->OnVerticalInput.RemoveDynamic(this, &AAvatarHandler::OnGetVerticalInput);
    APIEvents->OnVerticalInput.AddDynamic(this, &AAvatarHandler::OnGetVerticalInput);
}
void AAvatarHandler::OnGetHorizontalInput(float value)
{
    FRotator NewRotation = FRotator(0, -value * 30, 0);
    FQuat QuatRotation = FQuat(NewRotation);
    AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

void AAvatarHandler::OnGetVerticalInput(float value)
{
}
// Called every frame
void AAvatarHandler::Tick(float DeltaTime)
{
    Super::Tick(DeltaTime);
}

void AAvatarHandler::LoadParents()
{
    const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    FActorSpawnParameters spawnparams;
    spawnparams.Owner = this;

    if (m_AllModelParent == nullptr)
    {
        if (BP_EmptyActor != nullptr)
        {
            m_AllModelParent = GetWorld()->SpawnActor<AEmptyActor>(BP_EmptyActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            m_AllModelParent->AttachToActor(this, AttachmentTransformRules);
#if PLATFORM_APPLE
            // m_AllModelParent->SetActorLabel(FString("AllModelParent"));
#endif
        }
    }

    if (SpawnedOnBoardingParent == nullptr)
    {
        if (BP_EmptyActor != nullptr)
        {
            SpawnedOnBoardingParent = GetWorld()->SpawnActor<AEmptyActor>(BP_EmptyActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            SpawnedOnBoardingParent->AttachToActor(m_AllModelParent, AttachmentTransformRules);
#if PLATFORM_APPLE
            // SpawnedOnBoardingParent->SetActorLabel(FString("BoardingParent"));
#endif
        }
    }

    if (HomeModelParent == nullptr)
    {
        if (BP_EmptyActor != nullptr)
        {
            HomeModelParent = GetWorld()->SpawnActor<AEmptyActor>(BP_EmptyActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            HomeModelParent->AttachToActor(m_AllModelParent, AttachmentTransformRules);
#if PLATFORM_APPLE
            // HomeModelParent->SetActorLabel(FString("HomeModelParent"));
#endif
        }
    }

    if (CustomizeDefaultAvatarLoader == nullptr)
    {
        if (BP_CustomizeAvatarLoader != nullptr)
        {
            CustomizeDefaultAvatarLoader = GetWorld()->SpawnActor<ACustomizeAvatarLoader>(BP_CustomizeAvatarLoader, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            CustomizeDefaultAvatarLoader->AttachToActor(m_AllModelParent, AttachmentTransformRules);
#if PLATFORM_APPLE
            // CustomizeDefaultAvatarLoader->SetActorLabel(FString("CustomizeDefaultAvatarLoader"));
#endif
        }
    }

    if (customizeAvatarLoader == nullptr)
    {
        if (BP_CustomizeAvatarLoader != nullptr)
        {
            customizeAvatarLoader = GetWorld()->SpawnActor<ACustomizeAvatarLoader>(BP_CustomizeAvatarLoader, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            customizeAvatarLoader->AttachToActor(m_AllModelParent, AttachmentTransformRules);

#if PLATFORM_APPLE
            //  customizeAvatarLoader->SetActorLabel(FString("customizeAvatarLoader"));
#endif
        }
    }
}
void AAvatarHandler::LoadHomePanelModel(FString modelurl,TFunction<void()> OnComplete)
{
    if (GltfFullActorHome == nullptr)
    {
        APIEvents->ShowLoading();
        ULoadTextureFromURL::LoadByte(modelurl, [this,OnComplete](TArray<uint8> result) {
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
        if (BP_GltfFullActorHome != nullptr)
        {
            const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
            GltfFullActorHome = GetWorld()->SpawnActor<AGltfFullActor>(BP_GltfFullActorHome, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
            GltfFullActorHome->Asset = Asset;
            GltfFullActorHome->AttachToActor(HomeModelParent, AttachmentTransformRules);
            GltfFullActorHome->LoadModel();
        }
        OnComplete();
        APIEvents->HideLoading();
        });
    } else {
      OnComplete();
    }
}


void AAvatarHandler::RotateActor(float DeltaTime, FVector TouchLocation)
{

    float RotationSpeed = 1.0f;
    // Get the actor's current rotation
    FRotator ActorRotation = GetActorRotation();

    // Calculate the desired rotation based on touch input
    float YawChange = TouchLocation.X * RotationSpeed * DeltaTime;

    // Update the actor's rotation
    ActorRotation.Yaw += YawChange;
    SetActorRotation(ActorRotation);
     UE_LOG(LogTemp, Display, TEXT("RotateActor"));
}

void AAvatarHandler::RotateOnSwipe(FVector SwipeDirection)
{
    // Calculate the desired rotation based on the swipe direction
    FRotator NewRotation = GetActorRotation();
    NewRotation.Yaw += SwipeDirection.X; // Adjust the rotation as needed

    // Set the new rotation
    SetActorRotation(NewRotation);
     UE_LOG(LogTemp, Display, TEXT("RotateOnSwipe"));
}
void AAvatarHandler::SetModelParentEnable(EModelParent modelParent)
{

    UE_LOG(LogTemp, Display, TEXT("SetModelParentEnable"));

    if (HomeModelParent)
    {
        HomeModelParent->SetActorLocation(FVector(0, 0, 1000));
    }
    if (CustomizeDefaultAvatarLoader)
    {
        CustomizeDefaultAvatarLoader->SetActorLocation(FVector(0, 0, 1000));
    }
    if (customizeAvatarLoader)
    {
        customizeAvatarLoader->SetActorLocation(FVector(0, 0, 1000));
    }
    if (ForCustomizeAvatar)
    {
        ForCustomizeAvatar->SetActorLocation(FVector(0, 0, 1000));
    }

    switch (modelParent)
    {
    case EModelParent::ONBOARD:
        if (SpawnedOnBoardingParent)
        {
            SpawnedOnBoardingParent->SetActorLocation(FVector(0, 0, 0));
        }
        break;

    case EModelParent::HOME:
        if (HomeModelParent)
        {
            HomeModelParent->SetActorLocation(FVector(0, 0, 0));
        }
        break;

    case EModelParent::CUSTOMIZE:
        if (ForCustomizeAvatar)
        {
            ForCustomizeAvatar->SetActorLocation(FVector(0, 0, 0));
        }
        break;

    case EModelParent::NONE:
        break;
    }
}

void AAvatarHandler::LoadTheDefaultHead()
{
    UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->LoadTheDefaultHead"));
    // CustomizeDefaultAvatarLoader->LoadDefaultModel();
    customizeAvatarLoader->LoadCustomizeModel();
}

void AAvatarHandler::ResetToCurrentSelected()
{
    CustomizeDefaultAvatarLoader->SetActorHiddenInGame(false);
}

void AAvatarHandler::SetCurrentAvatarDetail()
{
    // ACurrentAvatarChanges* AvatarCurrentChangesInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
    CurrentSelectedBodyParts.Empty();
    if (AvatarChangesInstance)
    {
        UE_LOG(LogTemp, Display, TEXT("AvatarCurrentChangesInstance--300-start-->>>>"));
        AvatarChangesInstance->currentProps = FProps();
        AvatarChangesInstance->changedProps = FProps();
        AvatarChangesInstance->changeBlendShapes = TArray<FBlendShapeValue>();
        AvatarChangesInstance->currentBlendShapes = TArray<FBlendShapeValue>();
        CurrentSelectedBodyParts.Empty();
        for (const FProp &item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData)
        {
            FProp tempItem;
            tempItem.CoreBucket = item.CoreBucket;
            tempItem.ID = item.ID;

            AvatarChangesInstance->changedProps.props.Add(tempItem);
            AvatarChangesInstance->currentProps.props.Add(tempItem);
            AddCurrentBodyPart(EconomyItemHolder->GetEconomyItemWithId(item.ID));
        }

        for (const FBlendShapeValue &item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Blendshapes)
        {
            AvatarChangesInstance->changeBlendShapes.Add(item);
            AvatarChangesInstance->currentBlendShapes.Add(item);
        }

        FString hairColor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.HairColor;
        FString eyebrowcolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.EyebrowColor;
        FString facialhaircolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.FacialHairColor;
        FString lipcolor = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.ColorMeta.LipColor;

        AvatarChangesInstance->changePropColors.HairColor = AvatarChangesInstance->currentpropColors.HairColor = hairColor;
        AvatarChangesInstance->changePropColors.EyebrowColor = AvatarChangesInstance->currentpropColors.EyebrowColor = eyebrowcolor;
        AvatarChangesInstance->changePropColors.FacialHairColor = AvatarChangesInstance->currentpropColors.FacialHairColor = facialhaircolor;
        AvatarChangesInstance->changePropColors.LipColor = AvatarChangesInstance->currentpropColors.LipColor = lipcolor;
        UE_LOG(LogTemp, Display, TEXT("TimerHandle_DelayedCall--300-start-->>>>"));
        FTimerHandle TimerHandle_DelayedCall;
        GetWorldTimerManager().SetTimer(TimerHandle_DelayedCall, this, &AAvatarHandler::DelayedFunction, 3.0f, false);
    }
}

void AAvatarHandler::DelayedFunction()
{
    UE_LOG(LogTemp, Display, TEXT("DelayedFunction--END-->>>>"));
    // LoadInventoryPropDetail();
}
void AAvatarHandler::LoadInventoryPropDetail() {
  



    // UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->LoadInventoryPropDetail"));
    // //    TArray<Prop> NewProps;
    // // ACurrentAvatarChanges* AvatarInstance = Cast<ACurrentAvatarChanges>(UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass()));
    // if (AvatarChangesInstance != nullptr)
    // {
    //     UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->AvatarChangesInstance Prop Details"));
    //     for (const FProp &Item : AvatarChangesInstance->currentProps.props)
    //     {
    //         FProp NewProp;
    //         NewProp.CoreBucket = Item.CoreBucket;
    //         NewProp.ID = Item.ID;
    //         Props.Add(NewProp);
    //     }

    //     OnQueProp();
    // }
}
void AAvatarHandler::LoadInventoryPropDetail(TFunction<void()> OnComplete) {



  

}
void AAvatarHandler::OnQueProp()
{
    if (Props.Num() == 0)
    {
        // for (int k = 0 ; k < CurrentSelectedBodyParts.Num();k++)
        // {
        //     customizeAvatarLoader->DownloadModelfromData(CurrentSelectedBodyParts[k]);
        // }
        // OnPropProcessed.Broadcast();
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->PROP QUEUE"));
        FProp proper = Props[0];
        proper.CoreBucket = Props[0].CoreBucket;
        proper.ID = Props[0].ID;
        Props.RemoveAt(0);
        LoadPropDetail(proper);
    }
}
void AAvatarHandler::OnQueProp(TFunction<void()> OnComplete)
{
    if (Props.Num() == 0)
    {
        OnComplete();
    }
    else
    {
        UE_LOG(LogTemp, Display, TEXT("===OnComplete===> BP AvatarHandler->PROP QUEUE"));
        FProp proper = Props[0];
        proper.CoreBucket = Props[0].CoreBucket;
        proper.ID = Props[0].ID;
        Props.RemoveAt(0);
        LoadPropDetail(proper, OnComplete);
    }
}
void AAvatarHandler::LoadPropDetail(FProp prop)
{
    UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->LoadPropDetail"));
    if (!EconomyItemHolder->IsEconomyItemPresent(prop.ID))
    {
        UE_LOG(LogTemp, Display, TEXT("======> BP AvatarHandler->IsEconomyItemPresent"));
        UEconomyHandler::GetEconomyItemsByID(prop.ID, OnGetEconomyItemsByIDResult, OnGetEconomyItemsByIDError);
    }
    else
    {
        OnQueProp();
    }
}

void AAvatarHandler::LoadPropDetail(FProp prop, TFunction<void()> OnComplete)
{
    if (!EconomyItemHolder->IsEconomyItemPresent(prop.ID))
    {
        UEconomyHandler::GetEconomyItemsByID(
            prop.ID, [this, OnComplete](FGetEconomyItemsByIDResult result)
            {
            UE_LOG(LogTemp, Display,TEXT("======> BP AvatarHandler->GetEconomyItemsByID%s"),*result.Status);
            int gender = 3;
            UAvataryugData* AvataryugDataInstance = NewObject<UAvataryugData>();
            if(AvataryugDataInstance->IsCommonGender(result.Data.ItemCategory))
            {
                gender = 3;
            }
            else
            {
                switch (UserDetailHolder->UserDetails.Gender)
                {
                    case EGender::MALE:
                    gender = 1;
                    break;    
                    
                    case EGender::FEMALE:
                    gender = 2;
                    break;
                }
            }
            UEconomyHandler::GetEconomyItems(result.Data.ItemCategory,1,gender,0,500,[this,OnComplete](FGetEconomyItemsResult result)
            {
                UE_LOG(LogTemp, Display,TEXT("======> BP AvatarHandler->GetEconomyItems%s"),*result.Status);
                EconomyItemHolder->AddEconomyItemData(result);
                OnQueProp(OnComplete);

            },[this,OnComplete](FApiException error)
            {
                UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"), *error.ErrorMessage);
                OnQueProp([this,OnComplete]{
                    OnComplete();
                });
            }); },
            [this, OnComplete](FApiException error)
            {
                OnQueProp(OnComplete);

                UE_LOG(LogTemp, Display, TEXT("ON GetEconomyItemsByID ERROR--->>%s"), *error.ErrorMessage);
            });
    }
    else
    {
        OnQueProp(OnComplete);
    }
}

void AAvatarHandler::ApiEvents_ResetToDefault(TFunction<void()> OnComplete)
{
    UE_LOG(LogTemp, Display, TEXT("ON ApiEvents_ResetToDefault--->>"));
    FTransform OriginalTransform = CustomizeDefaultAvatarLoader->GetActorTransform();
    // GetWorld()->SpawnActor<ACustomParent>(OriginalTransform.GetTranslation(), OriginalTransform.GetRotation().Rotator());
    // ACustomizeAvatarLoader* NewActor =  GetWorld()->SpawnActor<ACustomizeAvatarLoader>(OriginalTransform.GetTranslation(), OriginalTransform.GetRotation().Rotator());
    if (CustomizeDefaultAvatarLoader)
    {
        TArray<AActor *> AttachedActors;
        CustomizeDefaultAvatarLoader->GetAttachedActors(AttachedActors);

        // Iterate through the attached actors and print their names
        for (AActor *AttachedActor : AttachedActors)
        {
            FString AttachedActorName;
            AttachedActorName = AttachedActor->GetName();
            UE_LOG(LogTemp, Warning, TEXT("Attached Actor Name: %s"), *AttachedActorName);
        }
        if (ForCustomizeAvatar)
        {
            if (ForCustomizeAvatar->spawnedHeadActor == nullptr)
            {
                FActorSpawnParameters spawnparams;
                spawnparams.Owner = this;
                // FTransform headTransform;
                // headTransform = AttachedActor->GetActorTransform();
                const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                // ForCustomizeAvatar->spawnedHeadActor = GetWorld()->SpawnActor<AHeadActor>(ForCustomizeAvatar->BP_HeadActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);

                // ForCustomizeAvatar->spawnedHeadActor->AttachToActor(SpawnedCustomizeDefaultParentClone, AttachmentTransformRules);

                // ForCustomizeAvatar->spawnedHeadActor->SetBodyMaterial(ForCustomizeAvatar->HeadDynamicMaterial);
                // ForCustomizeAvatar->spawnedHeadActor->SetEyeMaterial(ForCustomizeAvatar->EyeballDynamicMaterial);

                // ForCustomizeAvatar->LoadDefaultModels();
            }
        }
        if (CustomizeDefaultAvatarLoader->LoadedModelList.Num() >= 4)
        {
            // for (int k = 0; k <  ForCustomizeAvatar->bodyPoints.Num(); k++)
            // {
            //     FActorSpawnParameters spawning;
            //     spawning.Owner = this;
            //     const FAttachmentTransformRules AttacherRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
            //     AGltfActor* mode =  GetWorld()->SpawnActor<AGltfActor>( ForCustomizeAvatar->BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawning);
            //     mode->Asset = CustomizeDefaultAvatarLoader->GltfModelList[k]->Asset;
            //     mode->SetActorLabel(CustomizeDefaultAvatarLoader->GltfModelList[k]->MainCategory,true);
            //     mode->LoadModel(CustomizeDefaultAvatarLoader->GltfModelList[k]->MainCategory);
            //     ForCustomizeAvatar->LoadedModelList.Add(mode);
            //     mode->AttachToActor(ForCustomizeAvatar->bodyPoints[k], AttacherRules);

            // }

            for (int j = 0; j < CustomizeDefaultAvatarLoader->LoadedModelList.Num(); j++)
            {
                for (int l = 0; l < CustomizeDefaultAvatarLoader->LoadedModelList[j]->bothSkeletal.Num(); l++)
                {
                    CustomizeDefaultAvatarLoader->LoadedModelList[j]->bothSkeletal[l]->SetVisibility(false);
                }
            }
            CustomizeDefaultAvatarLoader->spawnedHeadActor->SkeletalHeadComponent->SetVisibility(false);
            CustomizeDefaultAvatarLoader->SetActorHiddenInGame(true);
        }

        OnComplete();
    }
    else
    {
        OnComplete();
        UE_LOG(LogTemp, Display, TEXT("ON ----NewActor---Nulll->>"));
    }

    // Disable the customizeDefaultAvatarLoader component
    // CustomizeDefaultAvatarLoader->SetVisibility(false);

    // // Check if ForCustomizeAvatar is valid and destroy it
    // if (ForCustomizeAvatar)
    // {
    //     ForCustomizeAvatar->DestroyComponent();
    // }

    // // Instantiate ForCustomizeAvatar by creating a new UStaticMeshComponent
    // ForCustomizeAvatar = NewObject<UStaticMeshComponent>(m_AllModelParent, UStaticMeshComponent::StaticClass());

    // // Set the properties of ForCustomizeAvatar, such as the static mesh, transform, etc.
    // // Example:
    // // ForCustomizeAvatar->SetStaticMesh(YourStaticMesh);
    // // ForCustomizeAvatar->SetWorldTransform(YourTransform);

    // // Attach ForCustomizeAvatar to the m_AllModelParent component/actor
    // ForCustomizeAvatar->AttachToComponent(m_AllModelParent->GetRootComponent(), FAttachmentTransformRules::SnapToTargetNotIncludingScale);
    // ForCustomizeAvatar->LoadDefaultModels();

    // OnComplete();
}

void AAvatarHandler::GetEconomyItemsByIDReply(FGetEconomyItemsByIDResult result)
{
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY SUCCESS--->>%s"), *result.Status);
    int gender = 3;
    UAvataryugData *AvataryugDataInstance = NewObject<UAvataryugData>();
    if (AvataryugDataInstance->IsCommonGender(result.Data.ItemCategory))
    {
        gender = 3;
    }
    else
    {
        switch (UserDetailHolder->UserDetails.Gender)
        {
        case EGender::MALE:
            gender = 1;
            break;

        case EGender::FEMALE:
            gender = 2;
            break;
        }
    }
    UEconomyHandler::GetEconomyItems(result.Data.ItemCategory, 1, gender, 0, 500, OnGetEconomyItemsResult, OnGetEconomyItemsError);
    // economyItemsList.Add(result.Data);
    // BDI_PriceText->SetText(FText::FromString(result.Data.DisplayName));
    //  APIEvents->HideLoading();
}
void AAvatarHandler::GetEconomyItemsByIDApiError(FApiException error)
{
    OnQueProp();
    //  APIEvents->HideLoading();
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"), *error.ErrorMessage);
}
void AAvatarHandler::OnReceiveEconomyItems(FGetEconomyItemsResult result)
{
    EconomyItemHolder->AddEconomyItemData(result);
    OnQueProp();
    CurrentSelectedProp = FEconomyItems();
    for (const FProp &item : UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.BucketData)
    {
        FProp tempItem;
        tempItem.CoreBucket = item.CoreBucket;
        tempItem.ID = item.ID;
        AvatarChangesInstance->currentProps.props.Add(tempItem);
        AvatarChangesInstance->changedProps.props.Add(tempItem);

        AddCurrentBodyPart(EconomyItemHolder->GetEconomyItemWithId(item.ID));
        // for (int k = 0 ; k < CurrentSelectedBodyParts.Num();k++)
        // {
        //     customizeAvatarLoader->EventLoadNetworkModel(true,CurrentSelectedBodyParts[k]);
        // }
    }
}
void AAvatarHandler::OnReceiveEconomyItemsError(FApiException result)
{
    OnQueProp();
}

void AAvatarHandler::RemovePart(FEconomyItems item)
{
    int index = -1;
    if (CurrentSelectedBodyParts.Num() > 0)
    {
        for (int i = 0; i < CurrentSelectedBodyParts.Num(); i++)
        {
            if (CurrentSelectedBodyParts[i].iD == item.iD)
            {
                index = i;
                break;
            }
        }
        if (index > -1)
        {
            CurrentSelectedBodyParts.RemoveAt(index);
        }
        AvatarChangesInstance->AddChangeProps(CurrentSelectedBodyParts);
    }
}

void AAvatarHandler::AddCurrentBodyPartWithid(FEconomyItems item)
{
    int index = -1;
    for (int i = 0; i < CurrentSelectedBodyParts.Num(); i++)
    {
        if (CurrentSelectedBodyParts[i].iD == item.iD)
        {
            index = i;
            break;
        }
        if (index > -1)
        {
            CurrentSelectedBodyParts.RemoveAt(index);
        }
        if (!item.iD.IsEmpty() && !item.itemCategory.IsEmpty())
        {
            CurrentSelectedBodyParts.Add(item);
        }
        AvatarChangesInstance->AddChangeProps(CurrentSelectedBodyParts);
    }
}
void AAvatarHandler::AddCurrentBodyPart(FEconomyItems item)
{
    UE_LOG(LogTemp, Display, TEXT("ON AddCurrentBodyPart SUCCESS--->>%s"), *item.iD);
    int index = -1;
    for (int i = 0; i < CurrentSelectedBodyParts.Num(); i++)
    {
        if (CurrentSelectedBodyParts[i].itemCategory == item.itemCategory)
        {
            index = i;
            break;
        }
    }
    if (index > -1)
    {
        CurrentSelectedBodyParts.RemoveAt(index);
    }
    if (!item.iD.IsEmpty() && !item.itemCategory.IsEmpty())
    {
        UE_LOG(LogTemp, Display, TEXT("ON CurrentSelectedBodyParts SUCCESS--->>%s"), *item.iD);
        CurrentSelectedBodyParts.Add(item);
    }
    AvatarChangesInstance->AddChangeProps(CurrentSelectedBodyParts);
}

void AAvatarHandler::LogOut()
{
    EconomyItemHolder->EconomyItems.Empty();
    typeOfPlatform = EAppType::GAME;
    TypeOfMontization = EMonitizeType::Monitize;
    APIEvents->isCustomize = false;
    CurrentSelectedProp = FEconomyItems();
    CurrentSelectedBodyParts.Empty();
    UserDetailHolder->UserDetails.currentUserSelectedAvatar = FUserAvatar();
    Props = TArray<FProp>();
}
void AAvatarHandler::DelayDuplicateModel()
{
    FTimerHandle Timer_Del;
    //  GetWorldTimerManager().SetTimer(TimerHandle_Del, this, &AAvatarLoaderBase::TestAddingDelay, 5.0f, false);
    GetWorldTimerManager().SetTimer(Timer_Del, this, &AAvatarHandler::DuplicateModel, 8.0f, false);
}

void AAvatarHandler::DuplicateModel()
{
    UE_LOG(LogTemp, Display, TEXT("CAlling DUplicateModel--->>"));
    if (customizeAvatarLoader != nullptr)
    {
        UE_LOG(LogTemp, Display, TEXT("Checked customizeAvatarLoader is not null--->>"));
        if (customizeAvatarLoader->bodyPoints.Num() >= 4)
        {
            UE_LOG(LogTemp, Display, TEXT("Checked customizeAvatarLoader bodyPoints > 0 --->>"));
            for (int k = 0; k < customizeAvatarLoader->bodyPoints.Num(); k++)
            {
                UE_LOG(LogTemp, Display, TEXT("Duplicating  bodyPoints --->>"));
                FActorSpawnParameters spawning;
                spawning.Owner = this;
                const FAttachmentTransformRules AttacherRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
                AGltfStaticActorPoint *point = GetWorld()->SpawnActor<AGltfStaticActorPoint>(ForCustomizeAvatar->BucketPoint_BP, FVector(0, 0, 0), FRotator(0, 0, 0), spawning);
                // point->SetActorLabel(FString(customizeAvatarLoader->bodyPoints[k]->BucketName));
                point->BucketName = customizeAvatarLoader->bodyPoints[k]->BucketName;
                // ForCustomizeAvatar->bodyPoints.Add(point);
                //    point->AttachToActor(SpawnedCustomizeDefaultParentClone, AttacherRules);
            }
        }

        // if(ForCustomizeAvatar->bodyPoints.Num() >= 4)
        // {
        //     for (int i = 0; i < ForCustomizeAvatar->bodyPoints.Num(); i++)
        //     {
        //         FActorSpawnParameters spawning;
        //         spawning.Owner = this;
        //         const FAttachmentTransformRules AttacherRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
        //         AGltfActor* mode =  GetWorld()->SpawnActor<AGltfActor>(ForCustomizeAvatar->BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawning);
        //         mode->Asset = customizeAvatarLoader->LoadedModelList[i]->Asset;
        //         mode->SetActorLabel(customizeAvatarLoader->LoadedModelList[i]->MainCategory,true);
        //         mode->LoadModel(customizeAvatarLoader->LoadedModelList[i]->MainCategory);
        //         ForCustomizeAvatar->LoadedModelList.Add(mode);
        //         mode->AttachToActor(ForCustomizeAvatar->bodyPoints[i], AttacherRules);
        //     }

        // }
    }
    //  for (int k = 0; k <  ForCustomizeAvatar->bodyPoints.Num(); k++)
    // {
    //     FActorSpawnParameters spawning;
    //     spawning.Owner = this;
    //     const FAttachmentTransformRules AttacherRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
    //     AGltfActor* mode =  GetWorld()->SpawnActor<AGltfActor>( ForCustomizeAvatar->BP_GltfActor, FVector(0, 0, 0), FRotator(0, 0, 0), spawning);
    //     mode->Asset = CustomizeDefaultAvatarLoader->GltfModelList[k]->Asset;
    //     mode->SetActorLabel(CustomizeDefaultAvatarLoader->GltfModelList[k]->MainCategory,true);
    //     mode->LoadModel(CustomizeDefaultAvatarLoader->GltfModelList[k]->MainCategory);
    //     ForCustomizeAvatar->LoadedModelList.Add(mode);
    //     mode->AttachToActor(ForCustomizeAvatar->bodyPoints[k], AttacherRules);

    // }
}