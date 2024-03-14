// Fill out your copyright notice in the Description page of Project Settings.
#include "OnBoardingTwoPanel.h"
#include "OnBoardingTwoAvatarButton.h"
#include "Components/VerticalBoxSlot.h"
#include "AvatarPresetsAPI/AvatarPresetsHandler.h"
#include "UserAccountManagementAPI/UserAccountManagementHandler.h"
#include "Components/SizeBox.h"
#include "Components/SizeBoxSlot.h"
#include "Components/CanvasPanelSlot.h"

void UOnBoardingTwoPanel::NativeConstruct()
{
    Super::NativeConstruct();
    if (CommonFunctionHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACommonFunction::StaticClass());
        CommonFunctionHolder = Cast<ACommonFunction>(FoundActor);
        if (CommonFunctionHolder == nullptr)
        {
            CommonFunctionHolder = GetWorld()->SpawnActor<ACommonFunction>();
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
    if (UserInventoryHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AUserInventoryHolder::StaticClass());
        UserInventoryHolder = Cast<AUserInventoryHolder>(FoundActor);
        if (UserInventoryHolder == nullptr)
        {
            UserInventoryHolder = GetWorld()->SpawnActor<AUserInventoryHolder>();
        }
    }
    if (AvatarHandler == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAvatarHandler::StaticClass());
        AvatarHandler = Cast<AAvatarHandler>(FoundActor);
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
    if (APIEvents == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AAPIEvents::StaticClass());
        APIEvents = Cast<AAPIEvents>(FoundActor);
        if (APIEvents == nullptr)
        {
            APIEvents = GetWorld()->SpawnActor<AAPIEvents>();
        }
        if (APIEvents)
        {
            // APIEvents->OnScreenOrientation.AddDynamic(this,&UOnBoardingThree::OnBoardingScreenOrientation);
            // APIEvents->HideLoading();
        }
    }

    if (CurrentAvatarChangesHolder == nullptr)
    {
        AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), ACurrentAvatarChanges::StaticClass());
        CurrentAvatarChangesHolder = Cast<ACurrentAvatarChanges>(FoundActor);
        // CurrentAvatarChangesHolder->SetActorLabel(FString("CurrentAvatarChangesHolder"));
    }

    LetsBeginWithAvatarButton->OnClicked.RemoveDynamic(this, &UOnBoardingTwoPanel::LoadArtifact);
    LetsBeginWithAvatarButton->OnClicked.AddDynamic(this, &UOnBoardingTwoPanel::LoadArtifact);

    CreateCustomButton->OnClicked.RemoveDynamic(this, &UOnBoardingTwoPanel::CreateCustomAvatar);
    CreateCustomButton->OnClicked.AddDynamic(this, &UOnBoardingTwoPanel::CreateCustomAvatar);

    SelectGenderCloseButton->OnClicked.RemoveDynamic(this, &UOnBoardingTwoPanel::CloseGenderPanel);
    SelectGenderCloseButton->OnClicked.AddDynamic(this, &UOnBoardingTwoPanel::CloseGenderPanel);

    MaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingTwoPanel::MaleGenderSelected);
    MaleButton->OnClicked.AddDynamic(this, &UOnBoardingTwoPanel::MaleGenderSelected);

    FemaleButton->OnClicked.RemoveDynamic(this, &UOnBoardingTwoPanel::FemaleGenderSelected);
    FemaleButton->OnClicked.AddDynamic(this, &UOnBoardingTwoPanel::FemaleGenderSelected);

    GetAvatarPresetsResult.BindUFunction(this, "OnGetAvatarPresetsResult");
    GetAvatarPresetsError.BindUFunction(this, "OnGetAvatarPresetsError");

    // onGltfModelHomeCallback.BindUFunction(this, "OnModelAssetHomeCallback");

    GrantAvatarPresetItemsToUserResponse.BindUFunction(this, "OnGrantAvatarPresetItemsToUserResponse");
    GrantAvatarPresetItemsToUserError.BindUFunction(this, "OnGrantAvatarPresetItemsToUserError");

    GrantAvatarToUserResponse.BindUFunction(this, "OnGrantAvatarToUserResponse");
    GrantAvatarToUserError.BindUFunction(this, "OnGrantAvatarToUserError");

    UpdateDefaultAvatarIDResult.BindUFunction(this, "OnUpdateDefaultAvatarIDResult");
    UpdateDefaultAvatarIDError.BindUFunction(this, "OnUpdateDefaultAvatarIDError");

    GetUsersAllAvatarsResult.BindUFunction(this, "OnGetUsersAllAvatarsResult");
    GetUsersAllAvatarsError.BindUFunction(this, "OnGetUsersAllAvatarsError");

    OnGetUserInventoryResult.BindUFunction(this, "GetUserInventoryResult");
    OnInventoryApiError.BindUFunction(this, "InventoryApiError");
}

void UOnBoardingTwoPanel::LetsBeginWithAvatar()
{
    APIEvents->ShowLoading();
    FClipExpressionData clipExpressionData;
    clipExpressionData.Style.ClipID = "standard_clip";
    clipExpressionData.Style.ExpressionID = "";
    UserDetailHolder->UserDetails.Gender = ArtifactList[scrollerindex].Gender == 2 ? EGender::FEMALE : EGender::MALE;
    if (UserDetailHolder->UserDetails.Gender == EGender::MALE)
    {
        clipExpressionData.gender = 0;
    }
    else if (UserDetailHolder->UserDetails.Gender == EGender::FEMALE)
    {
        clipExpressionData.gender = 1;
    }
    FString metaData;
    FJsonObjectConverter::UStructToJsonObjectString(clipExpressionData, metaData);

    FAvatarData avatarData;
    avatarData.AgeRange = ArtifactList[scrollerindex].AgeRange;
    avatarData.Race = ArtifactList[scrollerindex].Race;
    avatarData.Gender = UserDetailHolder->UserDetails.Gender == EGender::FEMALE ? 1 : 0;
    avatarData.CustomMetaData = ArtifactList[scrollerindex].CustomMetaData;

    FPropColors propcolors;
    FJsonObjectConverter::JsonObjectStringToUStruct(ArtifactList[scrollerindex].Color, &propcolors,0,0);
    avatarData.ColorMeta = propcolors;

    FProps props;
    FString propString = "{";
    propString.Append("\"props\":");
    propString.Append(ArtifactList[scrollerindex].Props);
    propString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(propString, &props,0,0);
    avatarData.BucketData = props.props;

    FBlendShapes blendshapes;
    FString blendString = "{";
    blendString.Append("\"blendShapes\":");
    blendString.Append(ArtifactList[scrollerindex].BlendshapeKeys);
    blendString.Append("}");
    FJsonObjectConverter::JsonObjectStringToUStruct(blendString, &blendshapes,0,0);

    for (int i = 0; i < blendshapes.blendShapes.Num(); i++)
    {
        FBlendShapeValue blendshape;
        blendshape.value = blendshapes.blendShapes[i].value;
        blendshape.shapekeys = blendshapes.blendShapes[i].shapekeys;
        avatarData.Blendshapes.Add(blendshape);
    }

    avatarData.MetaData = metaData;

    FGrantAvatarPresetItemsToUserRequest request;

    for (int i = 0; i < props.props.Num(); i++)
    {
        FGrantAvatarPresetItemsToUserRequestItemIDsInner item;
        item.ItemID = props.props[i].ID;
        request.ItemIDs.Add(item);
    }
    FJsonObjectConverter::UStructToJsonObjectString(avatarData, avatarDataStr);
    UE_LOG(LogTemp, Display, TEXT("==================  %s"), *avatarDataStr);

    UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(
        request, [this](FGrantAvatarPresetItemsToUserResponse result)
        {
       // UE_LOG(LogTemp, Display, TEXT("-------GET------GrantAvatarPresetItemsToUser------>%s"), *result.Status);
        FGrantAvatarToUserRequest grantAvatarRequest;
        grantAvatarRequest.AvatarData = avatarDataStr;
        UAvatarPresetsHandler::GrantAvatarPresetToUser(
            grantAvatarRequest, [this](FGrantAvatarToUserResponse gresult)
            {
                  //  UE_LOG(LogTemp, Display, TEXT("-------GET------GrantAvatarPresetToUser------>%s"), *gresult.Status);
                    CommonFunctionHolder->UpdateDefaultAvatarID(gresult.Data.AvatarID, [this,gresult]
                                                                { 
                                                                    UserDetailHolder->UserDetails.DefaultAvatarID = gresult.Data.AvatarID;
                                                                                                                      CommonFunctionHolder->GetCommonUserInventory([this]
                                                                                                                                                                   {
                       // UE_LOG(LogTemp, Display, TEXT("CommonFunctionHolder---GET--UserInventory--->Response------>"));
                        CommonFunctionHolder->GetUserAllAvatars([this]()
                                                                {
                                                                    DataHolder->cameFromFirstAvatar =true;
                                this->SetVisibility(ESlateVisibility::Hidden);
                                if (AvatarHandler->TypeOfMontization ==
                                        EMonitizeType::Monitize) {
               APIEvents->ShowPanel(EUIPanels::HOME, true);
                                } else {
                                       if(AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
    {
                                         AvatarHandler->customizeAvatarLoader
                                             ->LoadHeadModel([this] {
                                               LoadCurrentAvatarData([this] {
                                                 DataHolder->resetToCurrentModel =true;
                                                   APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
          });
      });
    }
    else
    {
      LoadCurrentAvatarData([this] {
        DataHolder->resetToCurrentModel =true;
          APIEvents->ShowPanel(EUIPanels::CUSTOMIZEFULL, true);
          });
    }
                                  }
                 

                                }); }); }); },
            [this](FApiException errorz)
            {
                APIEvents->HideLoading();
                APIEvents->ShowErrorNotification(FString::FromInt(errorz.ErrorCode), errorz.ErrorMessage);
               // UE_LOG(LogTemp, Display, TEXT("GrantAvatarPresetItemsToUser---ERROR--->%s"), *errorz.ErrorMessage);
            }); },
        [this](FApiException error)
        {
            APIEvents->HideLoading();
            APIEvents->ShowErrorNotification(FString::FromInt(error.ErrorCode), error.ErrorMessage);
            //  UE_LOG(LogTemp, Display, TEXT("UpdateUserDemographics---ERROR--->%s"), *error.ErrorMessage);
        });

    /// UAvatarPresetsHandler::GrantAvatarPresetItemsToUser(request, GrantAvatarPresetItemsToUserResponse, GrantAvatarPresetItemsToUserError);
}



void UOnBoardingTwoPanel::CreateCustomAvatar()
{
    DataHolder->isCustomizeAvatar = true;
    //  this->SetVisibility(ESlateVisibility::Hidden);
    SelectGenderPanel->SetVisibility(ESlateVisibility::Visible);
}
void UOnBoardingTwoPanel::CloseGenderPanel()
{
    SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
}
void UOnBoardingTwoPanel::MaleGenderSelected()
{
   // UE_LOG(LogTemp, Warning, TEXT("GENDER BUTTON IS CLICKED---: MALE"));
    OnClickMaleFemaleButton(EGender::MALE);
}
void UOnBoardingTwoPanel::FemaleGenderSelected()
{
   // UE_LOG(LogTemp, Warning, TEXT("GENDER BUTTON IS CLICKED---: FEMALE"));
    OnClickMaleFemaleButton(EGender::FEMALE);
}

void UOnBoardingTwoPanel::OnClickMaleFemaleButton(EGender gender)
{
    CurrentAvatarChangesHolder->changePropColors.EyebrowColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultEyebrowColor;
    CurrentAvatarChangesHolder->changePropColors.HairColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultHairColor;
    CurrentAvatarChangesHolder->changePropColors.FacialHairColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultFacialHairColor;
    if (gender == EGender::FEMALE)
    {
        CurrentAvatarChangesHolder->changePropColors.LipColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultLipColor;
        APIEvents->isMale = false;
    }
    if (gender == EGender::MALE)
    {
        CurrentAvatarChangesHolder->changePropColors.LipColor = AvatarHandler->CustomizeDefaultAvatarLoader->DefaultMaleLipColor;
        APIEvents->isMale = true;
    }

    TArray<AActor *> AttachedChildActors;
    AvatarHandler->SpawnedOnBoardingParent->GetAttachedActors(AttachedChildActors);
    for (AActor *AttachedActor : AttachedChildActors)
    {
        if (AttachedActor)
        {
            AttachedActor->Destroy();
        }
    }
    APIEvents->isCustomize = true;
    UserDetailHolder->UserDetails.Gender = gender;

    APIEvents->OnChangeCamera.Broadcast(CameraPanels::CustomizeAvatar_Head);
    AvatarHandler->customizeAvatarLoader->ResetData();
    if (AvatarHandler->customizeAvatarLoader->spawnedHeadActor == nullptr)
    {
        AvatarHandler->customizeAvatarLoader->LoadHeadModel([this]
                                                            {
            APIEvents->HideLoading();
            APIEvents->ShowLoading();
            APIEvents->HideLoading();
            ResetData();
            AvatarHandler->customizeAvatarLoader->ResetToDefault([this]
                                                                 {
                                                                     AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
                                                                     SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
                                                                     APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true);
                                                                     // AvatarHandler->CustomizeDefaultAvatarLoader->LoadDefaultModels();
                                                                 }); });
    }
    else
    {
        APIEvents->ShowLoading();
        APIEvents->HideLoading();
        ResetData();
        AvatarHandler->customizeAvatarLoader->ResetToDefault([this]
                                                             {
                                                                 // if(AvatarHandler->CustomizeDefaultAvatarLoader->count >= 4)
                                                                 // {
                                                                 //     APIEvents->OnResetToDefault.ExecuteIfBound([this]{
                                                                 //     UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---spawnedHeadActor--PRESENT->"));
                                                                 //     });
                                                                 // }
                                                                 AvatarHandler->ForCustomizeAvatar = AvatarHandler->customizeAvatarLoader;
                                                                 SelectGenderPanel->SetVisibility(ESlateVisibility::Hidden);
                                                                 APIEvents->ShowPanel(EUIPanels::CUSTOMIZEHEAD, true); });
        // AvatarHandler->ForCustomizeAvatar->ResetToDefault([this]
        //                                 { UE_LOG(LogTemp, Display, TEXT("On--OnResetToDefault--->EXECUTED---ForCustomizeAvatar--PRESENT->")); });
    }
    this->SetVisibility(ESlateVisibility::Hidden);
}


void UOnBoardingTwoPanel::LoadArtifact()
{
    FString artifactString = "{";
    artifactString.Append("\"artifacts\":");
    artifactString.Append(ArtifactList[scrollerindex].MeshArtifacts);
    artifactString.Append("}");
    FAvatarPresetArtifacts artifactlist;
    FJsonObjectConverter::JsonObjectStringToUStruct(artifactString, &artifactlist,0,0);
   // UE_LOG(LogTemp, Display, TEXT("LoadArtifact  %s"), *artifactString);
    if (artifactlist.artifacts.Num() > 0)
    {
        UserDetailHolder->tempmeshurl = artifactlist.artifacts[0].url;
    }
    LetsBeginWithAvatar();
}

void UOnBoardingTwoPanel::OnGrantAvatarPresetItemsToUserResponse(FGrantAvatarPresetItemsToUserResponse result)
{
  //  UE_LOG(LogTemp, Display, TEXT("OnGrantAvatarPresetItemsToUserResponse------>"));
    FGrantAvatarToUserRequest request;
    // request.UserID = UserDetailHolder->UserDetails.userID;
    request.AvatarData = avatarDataStr;
    UAvatarPresetsHandler::GrantAvatarPresetToUser(request, GrantAvatarToUserResponse, GrantAvatarToUserError);
}

void UOnBoardingTwoPanel::OnGrantAvatarPresetItemsToUserError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("OnGrantAvatarPresetItemsToUserResponse------>"));
}

void UOnBoardingTwoPanel::OnGrantAvatarToUserResponse(FGrantAvatarToUserResponse result)
{
  //  UE_LOG(LogTemp, Display, TEXT("On--GrantAvatar--->ToUserResponse------>%s"), *result.Data.AvatarID);

    FUpdateDefaultAvatarIDRequest request;
    request.DefaultAvatarID = result.Data.AvatarID;
    avatarid = result.Data.AvatarID;
    UDefaultHandler::UpdateDefaultAvatarID(request, UpdateDefaultAvatarIDResult, UpdateDefaultAvatarIDError);
}
void UOnBoardingTwoPanel::OnGrantAvatarToUserError(FApiException error)
{
}

void UOnBoardingTwoPanel::OnUpdateDefaultAvatarIDResult(FUpdateDefaultAvatarIDResult result)
{
    // APIEvents->HideLoading();
  //  UE_LOG(LogTemp, Display, TEXT("On--UpdateDefaultAvatarID--->Response------>%s"), *UserDetailHolder->UserDetails.userID);
    UUserItemManagementHandler::GetUserInventory(UserDetailHolder->UserDetails.userID, OnGetUserInventoryResult, OnInventoryApiError);
}

void UOnBoardingTwoPanel::OnUpdateDefaultAvatarIDError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("OnUpdateDefaultAvatarIDError--->error------>"));
}

void UOnBoardingTwoPanel::OnGetUsersAllAvatarsResult(FGetUsersAllAvatarsResult result)
{
    if (DataHolder != nullptr)
    {
        DataHolder->SynAvatars();
    }

   // UE_LOG(LogTemp, Display, TEXT("GET--UsersAllAvatars--->Response------>"));
    FString userid = UserDetailHolder->UserDetails.userID;
    FString platfrom = "Android";
    if (result.Data.Num() > 0)
    {
        UserDetailHolder->UserDetails.userAvatars.Empty();
        for (int i = 0; i < result.Data.Num(); i++)
        {
            FUserAvatar uservatar = FUserAvatar();
            uservatar.AvatarID = result.Data[i].AvatarID;

            FAvatarUrlDataList avatarurls;
            FString avatarurlstring = "{";
            avatarurlstring.Append("\"AvatarUrls\":");
            avatarurlstring.Append(result.Data[i].AvatarUrl);
            avatarurlstring.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(avatarurlstring, &avatarurls,0,0);
            uservatar.AvatarUrls = avatarurls.AvatarUrls;

            FAvatarThumbDataList thumburls;
            FString thumburlstring = "{";
            thumburlstring.Append("\"ThumbUrls\":");
            thumburlstring.Append(result.Data[i].ThumbUrl);
            thumburlstring.Append("}");
            FJsonObjectConverter::JsonObjectStringToUStruct(thumburlstring, &thumburls,0,0);
            uservatar.ThumbUrls = thumburls.ThumbUrls;

            UserDetailHolder->UserDetails.userAvatars.Add(uservatar);

            if (result.Data[i].AvatarID == UserDetailHolder->UserDetails.DefaultAvatarID)
            {
                UserDetailHolder->UserDetails.currentUserSelectedAvatar = uservatar;
            }
        }
        UserDetailHolder->UserDetails.Gender = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarData.Gender == 1 ? EGender::FEMALE : EGender::MALE;
    }
    this->SetVisibility(ESlateVisibility::Hidden);
    APIEvents->ShowPanel(EUIPanels::HOME, true);
}
void UOnBoardingTwoPanel::OnGetUsersAllAvatarsError(FApiException error)
{
}

void UOnBoardingTwoPanel::GetUserInventoryResult(FGetUserInventoryResult result)
{
   // UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->Response------>"));
    UserInventoryHolder->AddUserInventory(result.Data);
    UUserAccountManagementHandler::GetUsersAllAvatars(UserDetailHolder->UserDetails.userID, GetUsersAllAvatarsResult, GetUsersAllAvatarsError);
}

void UOnBoardingTwoPanel::InventoryApiError(FApiException error)
{
    UE_LOG(LogTemp, Display, TEXT("GET--UserInventory--->error------>"));
}

void UOnBoardingTwoPanel::OnGetAvatarPresetsResult(FGetAvatarPresetsResult result)
{
    //UE_LOG(LogTemp, Warning, TEXT("Code: %d"), result.Code);
    //UE_LOG(LogTemp, Warning, TEXT("Status: %s"), *result.Status);

    for (const FGetAvatarPresetsResultDataInner &InnerData : result.Data)
    {
       // UE_LOG(LogTemp, Warning, TEXT("InnerData MeshArtifacts: %s"), *InnerData.MeshArtifacts);
      //  UE_LOG(LogTemp, Warning, TEXT("------"));
      //  UE_LOG(LogTemp, Warning, TEXT("InnerData ImageArtifacts: %s"), *InnerData.ImageArtifacts);
    }
    ArtifactList.Empty();
    // ArtifactQueueList.Empty();
    for (int i = 0; i < result.Data.Num(); i++)
    {
        ArtifactList.Add(result.Data[i]);
        // ArtifactQueueList.Add(result.Data[i]);
    }
    // QueuePresetModel();
    ShowPropItems();
}

void UOnBoardingTwoPanel::OnGetAvatarPresetsError(FApiException error)
{
}

// void UOnBoardingTwoPanel::OnModelAssetHomeCallback(UglTFRuntimeAsset *asset)
// {
//     FActorSpawnParameters spawnparams;
//     spawnparams.Owner = AvatarHandler->ForCustomizeAvatar->SpawnedOnboardingParent;
//     if (BP_GltfFullActorHome != nullptr)
//     {
//         const FAttachmentTransformRules AttachmentTransformRules = FAttachmentTransformRules(EAttachmentRule::KeepRelative, true);
//         AGltfFullActor *GltfFullActorHome = GetWorld()->SpawnActor<AGltfFullActor>(BP_GltfFullActorHome, FVector(0, 0, 0), FRotator(0, 0, 0), spawnparams);
//         GltfFullActorHome->Asset = asset;
//         GltfFullActorHome->AttachToActor(AvatarHandler->ForCustomizeAvatar->SpawnedOnboardingParent, AttachmentTransformRules);
//         GltfFullActorHome->LoadModel();
//         GltfFullActorHome->SetActorHiddenInGame(false);
//         GltfFullActorList.Add(GltfFullActorHome);
//         // APIEvents->HideLoading();
//         // QueuePresetModel();
//     }
// }

void UOnBoardingTwoPanel::ResetData()
{
    CurrentAvatarChangesHolder->changedProps = FProps();
    for (int i = 0; i < CurrentAvatarChangesHolder->currentProps.props.Num(); i++)
    {
        FProp tempItem = CurrentAvatarChangesHolder->currentProps.props[i];
        CurrentAvatarChangesHolder->changedProps.props.Add(tempItem);
    }
    CurrentAvatarChangesHolder->changeBlendShapes = TArray<FBlendShapeValue>();
    for (int i = 0; i < CurrentAvatarChangesHolder->currentBlendShapes.Num(); i++)
    {
        CurrentAvatarChangesHolder->changeBlendShapes.Add(CurrentAvatarChangesHolder->currentBlendShapes[i]);
    }
    FString col = CurrentAvatarChangesHolder->currentpropColors.HairColor;
    CurrentAvatarChangesHolder->changePropColors.HairColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.FacialHairColor;
    CurrentAvatarChangesHolder->changePropColors.FacialHairColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.LipColor;
    CurrentAvatarChangesHolder->changePropColors.LipColor = col;

    col = CurrentAvatarChangesHolder->currentpropColors.EyebrowColor = col;
    CurrentAvatarChangesHolder->changePropColors.EyebrowColor = col;

    AvatarHandler->customizeAvatarLoader->ClearCurrent();
}
void UOnBoardingTwoPanel::LoadCurrentAvatarData(TFunction<void()> oncomplete) 
{
  FString avatari = UserDetailHolder->UserDetails.currentUserSelectedAvatar.AvatarID;
  UAvatarPresetsHandler::GetUserAvatarAllData(avatari,"Android", [this,oncomplete](FGetUserAvatarAllDataResponse result) 
  {
    AActor *FoundActor = UGameplayStatics::GetActorOfClass(GetWorld(), AEconomyItemHolder::StaticClass());
    AEconomyItemHolder *EconomyItemHolder = Cast<AEconomyItemHolder>(FoundActor);
    EconomyItemHolder->AddEconomyItemDataFromAvatar(result);
    oncomplete();
  },
  [this](FApiException error)
  {
    UE_LOG(LogTemp, Display, TEXT("ON GETECONOMY ERROR--->>%s"),*error.ErrorMessage);
  });
}

void UOnBoardingTwoPanel::LoadOnBoardingPanelDetail()
{
    APIEvents->ShowLoading();
    UAvatarPresetsHandler::GetAvatarPresets(3, 1, [this](FGetAvatarPresetsResult result)
    {
        ArtifactList.Empty();
        for (int i = 0; i < result.Data.Num(); i++)
        {
            ArtifactList.Add(result.Data[i]);
        }
        ShowPropItems(); 
    },
    [this](FApiException error)
    {
        UE_LOG(LogTemp, Display, TEXT("LoadOnBoarding-TWO-PanelDetail---error--->%s"), *error.ErrorMessage);
    });
}

void UOnBoardingTwoPanel::ShowPropItems()
{
    for (int i = 0; i < ArtifactList.Num(); i++)
    {
        UUserWidget *widget = CreateWidget(this, AvatarButton);
        OnboardingTwoScrollBox_1->AddChild(widget);
        UOnBoardingTwoAvatarButton *buttons = Cast<UOnBoardingTwoAvatarButton>(widget);
        buttons->SetButtonData(ArtifactList[i]);
        ButtonsH.Add(widget);
    }
    APIEvents->HideLoading();
}